#pragma once

#include "Event.h"
#include "Table.h"
#include "User.h"

#include <queue>

#include <set>
#include <unordered_map>
#include <vector>

namespace club {
class EventRepository {
public:
  void add_event(const Event& event) {
    M_storage_.push(event);
  }

  bool empty() const {
    return M_storage_.empty();
  }

  Event& front() {
    return M_storage_.front();
  }

  void pop() {
    M_storage_.pop();
  }

private:
  std::queue<Event> M_storage_;
};

struct UserNameComp {
  bool operator()(const User& u1, const User& u2) const {
    return u1.name() < u2.name();
  }
};

// Структура для хранения клиентов
class ClientRepository {
public:
  const User not_valid_client = User("", 0);

  void save_client(const User& client);

  std::size_t get_client_id(const std::string& name) const;

  std::string get_name_by_id(std::size_t id) const;

  std::pair<bool, std::size_t> find_client_id(const std::string& name) const;

  bool contains_client(const std::string& name) const;

  void remove_client(const std::string& name);

  auto begin() {
    return M_storage_.begin();
  }

  auto end() {
    return M_storage_.end();
  }

private:
  std::set<User, UserNameComp> M_storage_;
};

// Структура для хранения столов
class TableRepository {
public:
  TableRepository(std::size_t tables)
      : M_storage_(tables) {}

  void add_table_gain(std::size_t table_id, std::size_t gain) noexcept {
    M_storage_[table_id - 1].add_gain(gain);
  }

  void add_table_time(std::size_t table_id, Time time) noexcept {
    M_storage_[table_id - 1].add_working_time(time);
  }

  void set_table_sattime(std::size_t table_id, Time time) noexcept {
    M_storage_[table_id - 1].set_sat_time(time);
  }

  Time get_table_sattime(std::size_t table_id) const noexcept {
    return M_storage_[table_id - 1].get_sat_time();
  }

  std::size_t size() const noexcept {
    return M_storage_.size();
  }

  Table at(int table_id) const noexcept {
    return M_storage_[table_id - 1];
  }

  auto begin() {
    return M_storage_.begin();
  }

  auto end() {
    return M_storage_.end();
  }

private:
  std::vector<Table> M_storage_;
};

// Структура для связи клиента и стола
class TableOwnerRepository {
public:
  void assign_table(std::size_t table_id, std::size_t client_id);

  std::pair<bool, std::size_t> is_table_owned(std::size_t table_id) const;

  void free_table(std::size_t table_id);

  std::size_t get_tableId_by_userId(std::size_t user_id) const;

  std::vector<std::size_t> get_all_occupied_tables() const;

  std::size_t count_occupied_tables() const;

  bool all_free() const;

private:
  std::unordered_map<std::size_t, std::size_t> M_table_to_user_; // TableId -> UserId
  std::unordered_map<std::size_t, std::size_t> M_user_to_table; // UserId -> TableId
};

} // namespace club
