#pragma once

#include "Time.h"

#include <iostream>

namespace club {
enum class EventType {
  Arrived,
  Sat,
  Waiting,
  Left,
  Error,
  Success,
  Arrived_Saved,
  BAD_REQUEST,
  Waiting_Left
};

EventType parse_event_type(uint8_t type);

class Event {
public:
  Event() = default;

  Event(EventType event_type, Time time, std::string args)
      : M_args_(std::move(args))
      , M_type_(event_type)
      , M_time_stamp_(time) {}

  Time get_time() const noexcept {
    return M_time_stamp_;
  }

  EventType get_type() const noexcept {
    return M_type_;
  }

  std::string get_args() const noexcept {
    return M_args_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Event& event);

private:
  std::string M_args_{};
  EventType M_type_;
  Time M_time_stamp_;
};
} // namespace club
