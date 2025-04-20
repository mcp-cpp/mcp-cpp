//
//

#pragma once

namespace mcp {

template <typename SessionId, typename Session>
class Sessions {
 public:
  virtual ~Sessions() = default;

  virtual bool Contains(const SessionId& id) const = 0;

  virtual const Session& Get(const SessionId& id) const = 0;

  virtual void Emplace(const SessionId& id, const Session& session) = 0;

  // delete session, if session exist and deleted, return true
  virtual bool Erase(const SessionId& id) = 0;
};

}  // namespace mcp
