#include "Time.h"

#include <iomanip>
#include <regex>
#include <string>

club::Time::Time(int hour, int minute) noexcept
    : M_hour_(hour)
    , M_minute_(minute) {}

club::Time::Time(const std::string& time_str) {
  const std::regex time_regex("^([01]?[0-9]|2[0-3]):([0-5][0-9])$");
  std::smatch matches;

  if (!std::regex_match(time_str, matches, time_regex)) {
    throw club::parse_exception(time_str);
  }

  this->M_hour_ = std::stoi(matches[1].str());
  this->M_minute_ = std::stoi(matches[2].str());
}

int& club::Time::get_hour() noexcept {
  return this->M_hour_;
}

const int& club::Time::get_hour() const noexcept {
  return this->M_hour_;
}

int& club::Time::get_minute() noexcept {
  return this->M_minute_;
}

const int& club::Time::get_minute() const noexcept {
  return this->M_minute_;
}

bool club::Time::operator<(const Time& rhs) const noexcept {
  return get_hour() < rhs.get_hour() || (get_hour() == rhs.get_hour() && this->get_minute() < rhs.get_minute());
}

bool club::Time::operator>=(const Time& rhs) const noexcept {
  return !(*this < rhs);
}

club::Time& club::Time::operator+=(const Time& rhs) noexcept {
  this->get_minute() += rhs.get_minute();
  this->get_hour() += rhs.get_hour();
  if (this->get_minute() / 60 > 0) {
    this->get_hour() += this->get_minute() / 60;
    this->get_minute() %= 60;
  }
  return *this;
}

club::Time& club::Time::operator-=(const Time& rhs) noexcept {
  this->get_minute() -= rhs.get_minute();
  this->get_hour() -= rhs.get_hour();

  if (this->get_minute() < 0) {
    this->get_hour() -= 1;
    this->get_minute() += 60;
  }

  return *this;
}

club::Time club::Time::operator+(const Time& rhs) const noexcept {
  auto t = *this;
  t += rhs;
  return t;
}

club::Time club::Time::operator-(const Time& rhs) const noexcept {
  auto t = *this;
  t -= rhs;
  return t;
}

club::Time::operator std::string() const {
  std::ostringstream oss;
  oss << std::setw(2) << std::setfill('0') << static_cast<int>(get_hour()) << ":" << std::setw(2) << std::setfill('0')
      << static_cast<int>(get_minute());
  return oss.str();
}
