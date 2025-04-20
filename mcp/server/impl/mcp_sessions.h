//
//

#pragma once

#include <map>
#include <mutex>

#include "mcp/server/sessions.h"

namespace mcp {

// store sessions, thread safe
template <typename SessionId, typename Session>
class McpSessions final : public Sessions<SessionId, Session> {
 public:
  // 禁止拷贝构造和赋值
  McpSessions(const McpSessions&) = delete;
  McpSessions& operator=(const McpSessions&) = delete;

  // 默认构造函数
  McpSessions() = default;

  bool Contains(const SessionId& id) const override {
    std::lock_guard<std::mutex> lock(mutex_);
    return map_.find(id) != map_.end();
  }

  const Session& Get(const SessionId& id) const override {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = map_.find(id);
    if (it != map_.end()) {
      return it->second;
    }
    static Session default_empty_instance;
    return default_empty_instance;
  }

  void Emplace(const SessionId& id, const Session& session) override {
    std::lock_guard<std::mutex> lock(mutex_);
    auto result = map_.emplace(id, session);
  }

  bool Erase(const SessionId& id) override {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = map_.find(id);
    if (it != map_.end()) {
      map_.erase(it);
      return true;
    }
    return false;
  }

 private:
  std::map<SessionId, Session> map_{};
  mutable std::mutex mutex_;
};

}  // namespace mcp
