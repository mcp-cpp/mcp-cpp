//
//

#pragma once

#include <memory>
#include <string>

#include "mcp\common\context.h"

namespace mcp {

class ServerContext final : public Context {
 public:
  std::string request_message_;
};

using ServerContextPtr = std::shared_ptr<ServerContext>;

}  // namespace mcp
