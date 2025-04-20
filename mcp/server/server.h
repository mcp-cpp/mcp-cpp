//
//

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "mcp/common/session.h"
#include "mcp/io/response.h"
#include "mcp/io/transport_type.h"
#include "tool.h"

namespace mcp {

// server interface
class Server {
 public:
  virtual ~Server() = default;

  // server name
  [[nodiscard]] virtual std::string Name() const = 0;

  // server version
  [[nodiscard]] virtual std::string Version() const = 0;

  // server instructions
  [[nodiscard]] virtual std::string Instructions() const = 0;

  // server tools, using AddTool to add new tool
  [[nodiscard]] virtual const std::unordered_map<std::string, std::unique_ptr<Tool>>& Tools()
      const = 0;

  // add server tool
  virtual void AddTool(std::unique_ptr<Tool> tool) = 0;

  // io type, choose stdio or http SSE
  [[nodiscard]] virtual TransportType IoType() const = 0;

  // handle message
  [[nodiscard]] virtual Response HandleMessage(ServerContextPtr context) const = 0;

  // add filters soon

  // register session
  virtual void RegisterSession(const std::string& id, const Session& session) = 0;
  virtual void UnregisterSession(const std::string& id) = 0;

  // start service
  virtual bool Serve() = 0;
};

}  // namespace mcp
