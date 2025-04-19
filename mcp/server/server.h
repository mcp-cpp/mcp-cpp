//
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "tool.h"

namespace mcp {

class Server {
 public:
  virtual ~Server() = default;

  [[nodiscard]] virtual std::string Name() const = 0;

  [[nodiscard]] virtual std::string Version() const  = 0;

  [[nodiscard]] virtual std::string Instructions() const = 0;

  [[nodiscard]] virtual const std::unordered_map<std::string, std::unique_ptr<Tool>>& Tools() const = 0;
};

}  // namespace mcp
