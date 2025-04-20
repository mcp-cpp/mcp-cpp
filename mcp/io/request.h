//
//

#pragma once

#include <string>
#include <utility>

namespace mcp {

class Request {
 public:
  Request() = default;
  ~Request() = default;

  explicit Request(std::string json_str) : json_string_(std::move(json_str)) {}

  bool Parse() {
    return false;
  }

  [[nodiscard]] const std::string& ID() const {
    return id_;
  }

  // Method name
  [[nodiscard]] const std::string& Method() const {
    return method_;
  }

  // JSON-RPC version (always "2.0")
  [[nodiscard]] const std::string& JsonRpcVersion() const {
    return json_rpc_version_;
  }

  // Origin request content
  [[nodiscard]] const std::string& JsonString() const {
    return json_string_;
  }

 private:
  std::string id_;
  std::string method_;
  std::string json_rpc_version_ = "2.0";
  std::string json_string_;
};

}  // namespace mcp
