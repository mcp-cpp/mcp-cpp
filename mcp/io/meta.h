//
//


#pragma once

#include <string>

namespace mcp {

template <typename IdType = std::string>
struct Meta {
  std::string id_;
  std::string json_rpc_version_ = "2.0";
};

} // mcp
