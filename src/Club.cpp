#include "Club.h"

#include "Utils.h"

club::Time ComputerClub::close_time() const noexcept {
  return M_info.M_end_time_;
}

club::Time ComputerClub::open_time() const noexcept {
  return M_info.M_start_time_;
}

std::size_t ComputerClub::get_gain() const noexcept {
  return M_info.M_gain_;
}

std::size_t ComputerClub::get_price() const noexcept {
  return M_info.M_price_;
}

bool ComputerClub::all_tables_working() const noexcept {
  return M_info.M_tables_ == M_table_owner_rep_.count_occupied_tables();
}

std::size_t ComputerClub::get_amount_tables() const noexcept {
  return M_info.M_tables_;
}

ComputerClub::~ComputerClub() {
  while (!M_event_rep_.empty()) {
    std::cout << M_event_rep_.front() << '\n';
    M_event_rep_.pop();
  }

  for (const auto& user : M_client_rep_) {
    auto table_id = M_table_owner_rep_.get_tableId_by_userId(user.id());
    calc_gain(table_id, user.name(), close_time());
    std::cout << club::Event{club::EventType::Left, close_time(), user.name()} << '\n';
  }

  std::cout << close_time() << '\n';

  for (int table_id = 1; table_id <= M_table_rep_.size(); ++table_id) {
    std::cout << table_id << ' ' << M_table_rep_.at(table_id).get_gain() << ' '
              << M_table_rep_.at(table_id).get_working_time() << '\n';
  }
}

std::size_t ComputerClub::fetch_available_client_id() noexcept {
  return M_cur_client_id_++;
}

club::Event ComputerClub::handle_event(const club::Event& event) {
  using club::EventType;
  M_event_rep_.add_event(event);
  switch (event.get_type()) {
  case EventType::Arrived:
    return this->handle_arrived(event);
  case EventType::Left:
    return this->handle_left(event);
  case EventType::Sat:
    return this->handle_sat(event);
  case EventType::Waiting:
    return this->handle_waiting(event);
  default:
    throw std::runtime_error("[ERROR] Unknown event type");
  }
}

club::Event ComputerClub::handle_arrived(const club::Event& event) {
  if (event.get_time() >= close_time() || event.get_time() < open_time()) {
    M_event_rep_.add_event({club::EventType::Error, event.get_time(), "NotOpenYet"});
    return {club::EventType::Error, event.get_time(), "NotOpenYet"};
  }

  auto user_name = event.get_args();
  if (M_client_rep_.contains_client(user_name)) {
    M_event_rep_.add_event({club::EventType::Error, event.get_time(), "YouShallNotPass"});
    return {club::EventType::Error, event.get_time(), "YouShallNotPass"};
  }

  auto new_user = create_user(user_name);
  M_client_rep_.save_client(new_user);

  return {club::EventType::Success, event.get_time(), ""};
}

club::Event ComputerClub::handle_sat(const club::Event& event) {
  auto args = club::split(event.get_args());
  auto& client_name = args.at(0);
  std::size_t table_id = std::stoul(args.at(1));

  if (!M_client_rep_.contains_client(client_name)) {
    M_event_rep_.add_event({club::EventType::Error, event.get_time(), "ClientUnknown"});
    return {club::EventType::Error, event.get_time(), "ClientUnknown"};
  }

  std::size_t user_id = M_client_rep_.get_client_id(client_name);

  if (all_tables_working()) {
    M_event_rep_.add_event({club::EventType::Error, event.get_time(), "PlaceIsBusy"});
    return {club::EventType::Error, event.get_time(), "PlaceIsBusy"};
  }

  if (auto p = M_table_owner_rep_.is_table_owned(table_id); p.first && p.second == user_id) {
    M_event_rep_.add_event({club::EventType::Error, event.get_time(), "PlaceIsBusy"});
    return {club::EventType::Error, event.get_time(), "PlaceIsBusy"};
  } else if (p.first) {
    M_table_owner_rep_.free_table(table_id);
  }

  assign_table(table_id, user_id, event.get_time());

  return {club::EventType::Success, event.get_time(), event.get_args()};
}

club::Event ComputerClub::handle_waiting(const club::Event& event) {
  if (!all_tables_working()) {
    M_event_rep_.add_event({club::EventType::Error, event.get_time(), "ICanWaitNoLonger!"});
    return {club::EventType::Error, event.get_time(), "ICanWaitNoLonger!"};
  }

  auto user_name = event.get_args();
  if (M_waiting_queue_.size() == get_amount_tables()) {
    M_event_rep_.add_event({club::EventType::Waiting_Left, event.get_time(), user_name});
    return {club::EventType::Waiting_Left, event.get_time(), user_name};
  }

  std::size_t user_id;
  if (auto it = M_client_rep_.find_client_id(user_name); it.first) {
    user_id = it.second;
  } else {
    auto new_user = create_user(user_name);
    user_id = new_user.id();
  }

  M_client_rep_.save_client(user_name);
  M_waiting_queue_.push(user_id);

  return {club::EventType::Success, event.get_time(), user_name};
}

club::Event ComputerClub::handle_left(const club::Event& event) {
  auto user_name = event.get_args();

  auto [found, user_id] = M_client_rep_.find_client_id(user_name);
  if (!found) {
    M_event_rep_.add_event({club::EventType::Error, event.get_time(), "ClientUnknown"});
    return {club::EventType::Error, event.get_time(), "ClientUnknown"};
  }

  if (M_waiting_queue_.size() == get_amount_tables()) {
    M_event_rep_.add_event({club::EventType::Error, event.get_time(), "Waiting"});
    return {club::EventType::Error, event.get_time(), "Waiting"};
  }

  auto table_id = M_table_owner_rep_.get_tableId_by_userId(user_id);

  // Возможно следует это вставить в конце, а тут посчитать только рабочее время
  calc_gain(table_id, user_name, event.get_time());

  M_table_owner_rep_.free_table(table_id);
  M_client_rep_.remove_client(user_name);

  if (!M_waiting_queue_.empty()) {
    auto next_user_id = M_waiting_queue_.front();
    M_waiting_queue_.pop();
    assign_table(table_id, next_user_id, event.get_time());
    M_event_rep_.add_event({club::EventType::Sat, event.get_time(), M_client_rep_.get_name_by_id(next_user_id)});
  }

  return {club::EventType::Left, event.get_time(), user_name};
}

club::User ComputerClub::create_user(const std::string& name) noexcept {
  return club::User{name, fetch_available_client_id()};
}

void ComputerClub::calc_gain(std::size_t table_id, const std::string& user_name, club::Time timestamp) {
  auto sat_time = M_table_rep_.get_table_sattime(table_id);

  auto diff_time = timestamp - sat_time;

  auto paid_hours = diff_time.get_hour();
  if (diff_time.get_minute() > 0) {
    paid_hours++;
  }

  M_table_rep_.add_table_gain(table_id, paid_hours * get_price());
  M_info.M_gain_ += paid_hours * get_price();

  M_table_rep_.add_table_time(table_id, diff_time);
}
