//
//

#pragma once

#include <functional>
#include <string>

#include "mcp/server/server.h"

namespace mcp {

class McpServer : public Server {
 public:
  McpServer(std::string name, std::string version, std::string instructions);

  std::string Name() const override {
    return name_;
  }

  std::string Version() const override {
    return version_;
  }

  std::string Instructions() const override {
    return instructions_;
  }

  const std::unordered_map<std::string, std::unique_ptr<Tool>>& Tools() const override {
    return tools_;
  }

  void AddTool(std::unique_ptr<Tool> tool) override {
    tools_.emplace(tool->Name(), std::move(tool));
  }

  Response HandleMessage(ServerContextPtr context) const override;

 private:
  std::string name_;
  std::string version_;
  std::string instructions_;
  std::unordered_map<std::string, std::unique_ptr<Tool>> tools_;

  std::unordered_map<std::string, std::function<Response(ServerContextPtr)>> methods_handlers_;
};

}  // namespace mcp
