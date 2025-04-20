//
//

#include "mcp_server.h"

#include <utility>

#include "mcp/common/mcp_method.h"
#include "mcp/io/Response.h"
#include "mcp/io/json_rpc.h"
#include "mcp/io/request.h"

namespace mcp {

McpServer::McpServer(std::string name, std::string version, std::string instructions)
    : name_(std::move(name)), version_(std::move(version)), instructions_(std::move(instructions)) {
  methods_handlers_[kMethodInitialize] = [](ServerContextPtr ctx, const Request& request) {
    return {request.ID(), 0, "initialize success"};
  };
  methods_handlers_[kMethodPing] = [](ServerContextPtr ctx, const Request& request) {
    return {request.ID(), 0, "ping success"};
  };
  methods_handlers_[kMethodResourcesList] = [](ServerContextPtr ctx, const Request& request) {
    return {request.ID(), 0, "resources list success"};
  };
  methods_handlers_[kMethodResourcesTemplatesList] = [](ServerContextPtr ctx,
                                                        const Request& request) {
    return {request.ID(), 0, "resources templates list success"};
  };
  methods_handlers_[kMethodResourcesRead] = [](ServerContextPtr ctx, const Request& request) {
    return {request.ID(), 0, "resource read success"};
  };
  methods_handlers_[kMethodPromptsList] = [](ServerContextPtr ctx, const Request& request) {
    return {request.ID(), 0, "prompts list success"};
  };
  methods_handlers_[kMethodPromptsGet] = [](ServerContextPtr ctx, const Request& request) {
    return {request.ID(), 0, "prompts get success"};
  };
  methods_handlers_[kMethodToolsList] = [](ServerContextPtr ctx, const Request& request) {
    return {request.ID(), 0, "tools list success"};
  };
  methods_handlers_[kMethodToolsCall] = [](ServerContextPtr ctx, const Request& request) {
    return {request.ID(), 0, "tools call success"};
  };
}

Response McpServer::HandleMessage(ServerContextPtr context) const override {
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

}  // namespace mcp