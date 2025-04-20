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
  explicit McpSessions(const int max_capacity) : max_capacity_(max_capacity) {};

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

  bool Emplace(const SessionId& id, const Session& session) override {
    std::lock_guard<std::mutex> lock(mutex_);
    if (map_.size() >= max_capacity_) {
      return false;
    }
    map_.emplace(id, session);
    return true;
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

  [[nodiscard]] size_t MaxCapacity() const override {
    return max_capacity_;
  }

 private:
  std::map<SessionId, Session> map_{};
  mutable std::mutex mutex_;
  size_t max_capacity_{0};
};

}  // namespace mcp
