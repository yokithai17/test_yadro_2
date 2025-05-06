#include "Event.h"

#include "Utils.h"

std::ostream& club::operator<<(std::ostream& os, const Event& event) {
  os << event.get_time() << " " << event_type_to_id(event.get_type()) << " " << event.get_args();
  return os;
}
