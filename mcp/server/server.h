//
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "mcp/io/Response.h"
#include "mcp/io/io_type.h"
#include "tool.h"

namespace mcp {

class Server {
 public:
  virtual ~Server() = default;

  [[nodiscard]] virtual std::string Name() const = 0;

  [[nodiscard]] virtual std::string Version() const = 0;

  [[nodiscard]] virtual std::string Instructions() const = 0;

  [[nodiscard]] virtual const std::unordered_map<std::string, std::unique_ptr<Tool>>& Tools()
      const = 0;

  virtual void AddTool(std::unique_ptr<Tool> tool) = 0;

  [[nodiscard]] virtual Type IoType() const = 0;

  virtual Response HandleMessage(ServerContextPtr context) const = 0;
};

}  // namespace mcp
