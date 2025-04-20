//
//

#pragma once

#include <string>

#include "mcp/common/call_tool_request.h"
#include "mcp/server/server_context.h"

namespace mcp {

class Tool {
 public:
  virtual ~Tool() = default;

  [[nodiscard]] virtual std::string Name() const = 0;

  virtual void Handle(const ServerContextPtr& context, const CallToolRequest&) const = 0;
};

}  // namespace mcp
