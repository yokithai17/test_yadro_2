#pragma once

#include "Event.h"
#include "Repository.h"
#include "Time.h"
#include "Utils.h"

#include <queue>

namespace club {
struct ClubInfo {
  ClubInfo(std::size_t tables, std::size_t price, Time start, Time end) noexcept
      : M_tables_(tables)
      , M_price_(price)
      , M_start_time_(start)
      , M_end_time_(end) {}

  std::size_t M_tables_;
  std::size_t M_price_;
  std::size_t M_gain_{0};
  Time M_start_time_;
  Time M_end_time_;
};
} // namespace club

// Структура для компьютерного клуба
class ComputerClub {
public:
  ComputerClub() = delete;

  ComputerClub(std::size_t tables, std::size_t price, club::Time start, club::Time end) noexcept
      : M_info(tables, price, start, end)
      , M_table_rep_(tables) {}

  ~ComputerClub();

  club::Event handle_event(const club::Event& event);

  bool all_tables_working() const noexcept;

private:
  club::Event handle_left(const club::Event& event);

  club::Event handle_arrived(const club::Event& event);

  club::Event handle_waiting(const club::Event& event);

  club::Event handle_sat(const club::Event& event);

  std::size_t fetch_available_client_id() noexcept;

  club::Time close_time() const noexcept;

  club::Time open_time() const noexcept;

  std::size_t get_gain() const noexcept;

  std::size_t get_price() const noexcept;

  std::size_t get_amount_tables() const noexcept;

  club::User create_user(const std::string& name) noexcept;

  void calc_gain(std::size_t table_id, const std::string& user_name, club::Time timestamp);

  void assign_table(std::size_t table_id, std::size_t user_id, club::Time timestamp) noexcept {
    M_table_owner_rep_.assign_table(table_id, user_id);
    M_table_rep_.set_table_sattime(table_id, timestamp);
  }

  club::ClubInfo M_info;
  std::size_t M_cur_client_id_{0};
  club::EventRepository M_event_rep_;
  club::TableRepository M_table_rep_;
  club::ClientRepository M_client_rep_;
  club::TableOwnerRepository M_table_owner_rep_;
  // userId
  std::queue<std::size_t> M_waiting_queue_;
};
