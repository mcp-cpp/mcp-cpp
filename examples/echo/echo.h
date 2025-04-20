//
//

#pragma once

#include "mcp/server/impl/mcp_server.h"
#include "mcp/server/impl/mcp_tool.h"

namespace example {

int main() {
  mcp::McpServer server("echo server", "1.0.0", "output input content", mcp::TransportType::kStdIo);
  server.AddTool(std::make_unique<mcp::McpTool>(
      "echo", [](const mcp::ServerContextPtr& context, const mcp::CallToolRequest& call_tool_request) {
        return "echo success";
      }));
  server.Serve();
  return 0;
}

}  // namespace example
