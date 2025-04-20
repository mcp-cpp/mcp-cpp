//
//

#include "mcp_server.h"

#include <utility>

#include "mcp/io/Response.h"
#include "mcp/io/json_rpc.h"
#include "mcp/io/request.h"

namespace mcp {

McpServer::McpServer(std::string name, std::string version, std::string instructions)
    : name_(std::move(name)),
      version_(std::move(version)),
      instructions_(std::move(instructions)) {}

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
  return method(context);
}

}  // namespace mcp