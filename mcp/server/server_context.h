//
//

#pragma once

#include <memory>
#include <string>
#include <utility>

#include "mcp/common/context.h"

namespace mcp {

class ServerContext final : public Context {
 public:
  explicit ServerContext(std::string input) : request_message_(std::move(input)) {}

  std::string request_message_;
};

using ServerContextPtr = std::shared_ptr<ServerContext>;

}  // namespace mcp
