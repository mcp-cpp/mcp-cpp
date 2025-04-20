//
//

#pragma once

#include "mcp/server/impl/mcp_server.h"

namespace mcp {

class StdIoServer : public McpServer {
 public:
  Type IoType() const override {
    return Type::kStdIo;
  }
};

}  // namespace mcp
