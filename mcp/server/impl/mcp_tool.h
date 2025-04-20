//
//

#pragma once

#include <functional>
#include <utility>

#include "mcp/server/tool.h"

namespace mcp {

class McpTool final : public Tool {
 public:
  using HandlerFunc = std::function<void(const ServerContextPtr& context, const CallToolRequest&)>;

  McpTool(std::string name, HandlerFunc func)
      : name_(std::move(name)), handler_func_(std::move(func)) {}

  [[nodiscard]] std::string Name() const override {
    return name_;
  }

  void Handle(const ServerContextPtr& context, const CallToolRequest& call_tool_request) const override {
    return handler_func_(context, call_tool_request);
  }

 private:
  std::string name_;
  HandlerFunc handler_func_ = nullptr;
};

}  // namespace mcp
