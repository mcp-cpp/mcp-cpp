//
//

#pragma once

#include <string>
#include <utility>

#include "mcp/io/error_code.h"
#include "mcp/jsonrpc/identifier.h"

namespace mcp {

class Response {
 public:
  Response(Identifier id, ErrorCode code, std::string message)
      : id_(std::move(id)), code_(code), message_(std::move(message)) {};

  [[nodiscard]] std::string ToJson() const {
    return "";
  }

 private:
  Identifier id_;
  ErrorCode code_;
  std::string message_;
};

}  // namespace mcp
