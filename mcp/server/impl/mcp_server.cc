//
//

#include "mcp_server.h"

#include <utility>

#include "mcp/common/mcp_method.h"
#include "mcp/io/impl/sse_io_handler.h"
#include "mcp/io/impl/std_io_handler.h"
#include "mcp/io/json_rpc.h"
#include "mcp/io/request.h"
#include "mcp/io/response.h"

namespace mcp {

McpServer::McpServer(std::string name,
                     std::string version,
                     std::string instructions,
                     TransportType io_type)
    : name_(std::move(name)),
      version_(std::move(version)),
      instructions_(std::move(instructions)),
      io_type_(io_type) {
  methods_handlers_[kMethodInitialize] = [](ServerContextPtr ctx, const Request& request) {
    return Response(request.ID(), ErrorCode::kSuccess, "initialize success");
  };
  methods_handlers_[kMethodPing] = [](ServerContextPtr ctx, const Request& request) {
    return Response(request.ID(), ErrorCode::kSuccess, "ping success");
  };
  methods_handlers_[kMethodResourcesList] = [](ServerContextPtr ctx, const Request& request) {
    return Response(request.ID(), ErrorCode::kSuccess, "resources list success");
  };
  methods_handlers_[kMethodResourcesTemplatesList] = [](ServerContextPtr ctx,
                                                        const Request& request) {
    return Response(request.ID(), ErrorCode::kSuccess, "resources templates list success");
  };
  methods_handlers_[kMethodResourcesRead] = [](ServerContextPtr ctx, const Request& request) {
    return Response(request.ID(), ErrorCode::kSuccess, "resource read success");
  };
  methods_handlers_[kMethodPromptsList] = [](ServerContextPtr ctx, const Request& request) {
    return Response(request.ID(), ErrorCode::kSuccess, "prompts list success");
  };
  methods_handlers_[kMethodPromptsGet] = [](ServerContextPtr ctx, const Request& request) {
    return Response(request.ID(), ErrorCode::kSuccess, "prompts get success");
  };
  methods_handlers_[kMethodToolsList] = [](ServerContextPtr ctx, const Request& request) {
    return Response(request.ID(), ErrorCode::kSuccess, "tools list success");
  };
  methods_handlers_[kMethodToolsCall] = [](ServerContextPtr ctx, const Request& request) {
    return Response(request.ID(), ErrorCode::kSuccess, "tools call success");
  };
}

Response McpServer::HandleMessage(ServerContextPtr context) const {
  // parse message
  Request request;
  if (!request.Parse(context->request_message_)) {
    return {"", ErrorCode::kParseError, "Failed to parse request message"};
  }
  // Check for valid JSONRPC version
  if (request.JsonRpcVersion() != kJsonRpcVersion) {
    return {"", ErrorCode::kInvalidRequest, "Invalid JSON-RPC version"};
  }
  // find method
  const auto& method_iter = methods_handlers_.find(request.Method());
  if (method_iter == methods_handlers_.end()) {
    return {"", ErrorCode::kMethodNotFound, "Method not found"};
  }
  const auto& method = method_iter->second;
  return method(context, request);
}

bool McpServer::Serve() {
  if (IoType() == TransportType::kStdIo) {
    auto handler = std::make_unique<StdIoHandler>();
    handler->Handle(this);
  } else if (IoType() == TransportType::kSse) {
    auto handler = std::make_unique<SseIoHandler>();
    handler->Handle(this);
  } else {
    return false;
  }
  return true;
}

}  // namespace mcp