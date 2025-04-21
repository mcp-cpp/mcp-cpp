// Copyright (c) The Feeds Team. All rights reserved.

#include "request.h"

namespace jsonrpc {

Request::Request(std::string jsonrpc_version, std::string method, Json params, Identifier id)
    : jsonrpc_version_(std::move(jsonrpc_version)),
      method_(std::move(method)),
      params_(std::move(params)),
      id_(std::move(id)) {}

bool Request::Parse(const std::string& json_str) {
  try {
    auto j = Json::parse(json_str);
    from_json(j, *this);
  } catch (const nlohmann::json::parse_error& e) {
    return false;
  } catch (const std::exception& e) {
    return false;
  } catch (...) {
    return false;
  }
  return true;
}

// to_json()
void to_json(Json& j, const Request& req) {
  j = Json{{kJsonRpcVersionName, req.JsonrpcVersion()},
           {kMethodName, req.Method()},
           {kParamsName, req.Params()}};

  if (req.Id().Type() != Identifier::IdType::kNull) {
    j[kIdName] = req.Id().ToJson();
  }
}

// from_json()
void from_json(const Json& j, Request& req) {
  // at maybe throw exception
  const auto jsonrpc_version_ = j.at(kJsonRpcVersionName).get<std::string>();
  const auto method = j.at(kMethodName).get<std::string>();
  const auto& params = j.at(kParamsName);

  Identifier id;
  if (j.contains(kIdName)) {
    id.ParseJson(j.at(kIdName));
  }

  req = Request(jsonrpc_version_, method, params, id);
}

}  // namespace jsonrpc