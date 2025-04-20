//
//


#pragma once

#include "mcp\common\context.h"
#include <memory>

namespace mcp {

class ServerContext final : public Context {

};

using ServerContextPtr = std::shared_ptr<ServerContext>;

} // mcp
