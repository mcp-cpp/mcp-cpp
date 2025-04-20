//
//

#pragma once

#include <string>
#include <utility>

#include "mcp/io/error_code.h"

namespace mcp {

class Request {
 public:
  Request() = default;

  bool Parse(const std::string& json_str) {
    return false;
  }

  const std::string& ID() const {
    return id_;
  }

  const std::string& Method() const {
    return method_;
  }

  const std::string& JsonRpcVersion() const {
    return json_rpc_version_;
  }

 private:
  std::string id_;
  ErrorCode code_;
  std::string method_;
  std::string json_rpc_version_;
};

}  // namespace mcp
