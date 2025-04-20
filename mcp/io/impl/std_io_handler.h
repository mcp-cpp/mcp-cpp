//
//


#pragma once

#include "mcp/io/io_handler.h"

namespace mcp {

class StdIoHandler final : public IoHandler {
  public:
   void Handle(Server* server) override;
};

} // mcp
