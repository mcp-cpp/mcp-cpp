//
//

#pragma once

#include <functional>
#include <string>

#include "mcp/io/request.h"
#include "mcp/server/server.h"

namespace mcp {

class McpServer : public Server {
 public:
  McpServer(std::string name, std::string version, std::string instructions, Type io_type);

  using Handler = std::function<Response(ServerContextPtr ctx, const Request& request)>;

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

  [[nodiscard]] Type IoType() const override {
    return io_type_;
  }

  Response HandleMessage(ServerContextPtr context) const override;

  bool Serve() override;

 private:
  std::string name_;
  std::string version_;
  std::string instructions_;
  Type io_type_;
  std::unordered_map<std::string, std::unique_ptr<Tool>> tools_;

  std::unordered_map<std::string, Handler> methods_handlers_;
};

}  // namespace mcp
