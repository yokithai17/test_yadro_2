#pragma once

#include "Time.h"

#include <iostream>

namespace club {
class Table {
public:
  Table() = default;

  void add_gain(std::size_t gain) noexcept {
    M_gain_ += gain;
  }

  void add_working_time(Time time) noexcept {
    M_timestamp_ += time;
  }

  void set_sat_time(Time time) noexcept {
    M_start_sat_time_ = time;
  }

  Time get_working_time() const noexcept {
    return M_timestamp_;
  }

  Time get_sat_time() const noexcept {
    return M_start_sat_time_;
  }

  std::size_t get_gain() const noexcept {
    return M_gain_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Table& table) {
    os << table.get_working_time() << " " << table.get_gain();
    return os;
  }

private:
  Time M_timestamp_{0, 0};
  Time M_start_sat_time_{0, 0};
  std::size_t M_gain_{0};
};
} // namespace club
