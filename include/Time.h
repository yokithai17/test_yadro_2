#pragma once

#include <cstdint>
#include <stdexcept>

namespace club {
// Time - Структура для времени (24 - формате)
class Time {
public:
  Time() = default;

  Time(const Time&) = default;

  Time(int hour, int minute) noexcept;

  Time(const std::string& time_str);

  int& get_hour() noexcept;

  const int& get_hour() const noexcept;

  int& get_minute() noexcept;

  const int& get_minute() const noexcept;

  bool operator<(const Time& rhs) const noexcept;

  bool operator>=(const Time& rhs) const noexcept;

  bool operator==(const Time& time) const = default;

  Time& operator+=(const Time& rhs) noexcept;

  Time& operator-=(const Time& rhs) noexcept;

  Time operator+(const Time& rhs) const noexcept;

  Time operator-(const Time& rhs) const noexcept;

  friend std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << static_cast<std::string>(time);
    return os;
  }

  operator std::string() const;

private:
  int M_hour_{0};
  int M_minute_{0};
};

struct parse_exception : std::runtime_error {
  explicit parse_exception(const std::string& what) noexcept
      : runtime_error("[ERROR] Parse error " + what) {}
};
} // namespace club
