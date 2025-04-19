//
//


#pragma once

#include <string>

#include "mcp/common/call_tool_request.h"

namespace mcp {

class Tool {
  public:
  virtual ~Tool() = default;
   [[nodiscard]] virtual std::string Name() const = 0;

  virtual void Handle(CallToolRequest) const = 0;
};

} // mcp
