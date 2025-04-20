//

#pragma once

#include <string>

#include "third_party/nlohmann/json.hpp"

namespace mcp {

using json = nlohmann::json;

class JsonData {
 public:
  // 默认构造函数
  JsonData() = default;

  // 从 JSON 字符串初始化
  bool Parse(const std::string& json_str) {
    try {
      data_ = json::parse(json_str);
    } catch (const json::parse_error& e) {
      return false;
    }
    return true;
  }

  // 转换为 JSON 字符串
  [[nodiscard]] std::string ToString(int indent = 2) const {
    return data_.dump(indent);  // 格式化输出，缩进为 4 个空格
  }

  // 增加字段
  void AddField(const std::string& key, const json& value) {
    data_[key] = value;
  }

  // 删除字段
  bool RemoveField(const std::string& key) {
    if (data_.contains(key)) {
      data_.erase(key);
    } else {
      return false;
    }
    return true;
  }

  // 获取字段值（通用方法）
  template <typename T>
  bool GetField(const std::string& key, T& t) const {
    if (data_.contains(key)) {
      t = data_[key].get<T>();
    } else {
      return false;
    }
    return true;
  }

 private:
  json data_;
};

}  // namespace mcp
