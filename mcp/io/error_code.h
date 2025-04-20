//
//

#pragma once

namespace mcp {

// Standard JSON-RPC error codes
enum class ErrorCode : int {
  kParseError = -32700,
  kInvalidRequest = -32600,
  kMethodNotFound = -32601,
  kInvalid = -32602,
  kInternalError = -32603,
};

}  // namespace mcp