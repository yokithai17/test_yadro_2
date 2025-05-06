#pragma once

#include "Event.h"

#include <string>
#include <vector>

namespace club {

std::vector<std::string> split(const std::string& s, char delim = ' ', int amount = 2);

EventType id_to_event_type(const std::string& id_str);

int event_type_to_id(EventType type);

Event event_parse(const std::string& input);
} // namespace club
