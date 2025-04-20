//
//

#pragma once
#include "mcp/server/server.h"

namespace mcp {

class IoHandler {
 public:
  virtual ~IoHandler() = default;

  virtual void Handle(Server* server) = 0;
};

}  // namespace mcp
