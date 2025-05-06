#include "Utils.h"

#include <sstream>

namespace club {

std::vector<std::string> split(const std::string& s, char delim, int amount) {
  std::vector<std::string> elems;
  std::stringstream ss(s);
  std::string item;

  while (std::getline(ss, item, delim) && amount > 0) {
    elems.push_back(item);
    --amount;
  }

  return elems;
}

Event event_parse(const std::string& input) {
  std::istringstream iss(input);
  std::string time_token, type_token, args;

  if (!(iss >> time_token)) {
    throw parse_exception("Invalid input format: missing time");
  }

  if (!(iss >> type_token)) {
    throw parse_exception("Invalid input format: missing event type");
  }

  std::getline(iss >> std::ws, args);

  return {id_to_event_type(type_token), Time{time_token}, args};
}

// to input
EventType id_to_event_type(const std::string& id_str) {
  switch (std::stoi(id_str)) {
  case 1:
    return EventType::Arrived;
  case 2:
    return EventType::Sat;
  case 3:
    return EventType::Waiting;
  case 4:
    return EventType::Left;
  case 11:
    return EventType::Left;
  case 12:
    return EventType::Sat;
  case 13:
    return EventType::Error;
  default:
    return EventType::Error;
  }
}

// to output
int event_type_to_id(EventType type) {
  switch (type) {
  case EventType::Arrived:
    return 1;
  case EventType::Arrived_Saved:
    return 11;
  case EventType::Waiting:
    return 3;
  case EventType::Left:
    return 4;
  case EventType::Waiting_Left:
    return 11;
  case EventType::Sat:
    return 12;
  case EventType::Error:
    return 13;
  default:
    return -1;
  }
}
} // namespace club
