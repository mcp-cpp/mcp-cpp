// Copyright (c) The Feeds Team. All rights reserved.

#pragma once

#include <exception>
#include <string>
#include <vector>

#include "identifier.h"
#include "third_party/nlohmann/json.hpp"

namespace mcp {

auto kJsonRpcVersionName = "jsonrpc";
auto kMethodName = "method";
auto kParamsName = "params";
auto kIdName = "id";

// A rpc call is represented by sending a Request object to a Server. The Request object has the
// following members:
//
// jsonrpc
// A String specifying the version of the Json-RPC protocol. MUST be exactly "2.0".
// method
// A String containing the name of the method to be invoked. Method names that begin with the word
// rpc followed by a period character (U+002E or ASCII 46) are reserved for rpc-internal methods and
// extensions and MUST NOT be used for anything else. params A Structured value that holds the
// parameter values to be used during the invocation of the method. This member MAY be omitted. id
// An identifier established by the Client that MUST contain a String, Number, or NULL value if
// included. If it is not included it is assumed to be a notification. The value SHOULD normally not
// be Null [1] and Numbers SHOULD NOT contain fractional parts [2] The Server MUST reply with the
// same value in the Response object if included. This member is used to correlate the context
// between the two objects.
//
// [1] The use of Null as a value for the id member in a Request object is discouraged, because this
// specification uses a value of Null for Responses with an unknown id. Also, because Json-RPC 1.0
// uses an id value of Null for Notifications this could cause confusion in handling.
//
// [2] Fractional parts may be problematic, since many decimal fractions cannot be represented
// exactly as binary fractions.
class Request {
 public:
  Request() = default;

  Request(std::string jsonrpc_version, std::string method, Json params, Identifier id);

  // if failed returns false
  bool Parse(const std::string& json_str);

  [[nodiscard]] const Identifier& Id() const {
    return id_;
  }

  [[nodiscard]] const std::string& Method() const {
    return method_;
  }

  [[nodiscard]] const Json& Params() const {
    return params_;
  }

  [[nodiscard]] const std::string& JsonrpcVersion() const {
    return jsonrpc_version_;
  }

 private:
  std::string jsonrpc_version_ = "2.0";
  std::string method_;
  Json params_;
  Identifier id_;
};

// to_json() request convert to json
void to_json(Json& j, const Request& req);

// from_json() request convert from json
void from_json(const Json& j, Request& req);

}  // namespace jsonrpc
