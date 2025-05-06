#include "Event.h"

#include "Utils.h"
namespace club {
  std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << event.get_time() << " " << event_type_to_id(event.get_type()) << " " << event.get_args();
    return os;
  }
}
