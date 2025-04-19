//
//

#include "mcp_server.h"

#include <utility>

namespace mcp {

McpServer::McpServer(std::string name, std::string version, std::string instructions)
    : name_(std::move(name)),
      version_(std::move(version)),
      instructions_(std::move(instructions)) {}
}  // namespace mcp