#pragma once

#include "Time.h"

#include <string>

namespace club {
// Структура для хранения пользователя
class User {
public:
  User(const std::string& name, std::size_t id)
      : M_name_(name)
      , M_id_(id) {}

  User(const std::string& name)
      : M_name_(name) {}

  const std::string& name() const noexcept {
    return M_name_;
  }

  std::size_t id() const noexcept {
    return M_id_;
  }

private:
  std::string M_name_;
  std::size_t M_id_{0};
};
} // namespace club
