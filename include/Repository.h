#pragma once

#include "Event.h"
#include "Table.h"
#include "User.h"
#include "IRepository.h"

#include <queue>

#include <set>
#include <unordered_map>
#include <optional>
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
class InMemoryClientRepository : public IClientRepository {
public:
  const User not_valid_client = User("", 0);

  void save(const User& client);

  std::optional<std::size_t> get_client_id(const std::string& name) const;

  std::optional<std::string> get_name_by_id(std::size_t id) const override;

  std::optional<std::size_t> find_id(const std::string& name) const override;

  bool contains(const std::string& name) const override;

  void remove(const std::string& name) override;

  std::vector<User> last_users() const override;
private:
  std::set<User, UserNameComp> M_storage_;
};

// Структура для хранения столов
class InMemoryTableRepository : public ITableRepository {
public:
  InMemoryTableRepository(std::size_t tables)
      : M_storage_(tables) {}

  void add_gain(std::size_t table_id, std::size_t gain) noexcept override {
    M_storage_[table_id - 1].add_gain(gain);
  }

  void add_working_time(std::size_t table_id, Time time) noexcept override {
    M_storage_[table_id - 1].add_working_time(time);
  }

  void add_starttime(std::size_t table_id, Time time) noexcept override {
    M_storage_[table_id - 1].set_sat_time(time);
  }

  Time get_start_time(std::size_t table_id) const noexcept override {
    return M_storage_[table_id - 1].get_sat_time();
  }

  Table get_table(int table_id) const noexcept override {
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
class InMemoryTableOwnerRepository : public ITableOwnerRepository {
public:
  void assign(std::size_t table_id, std::size_t client_id) override;

  std::pair<bool, std::size_t> table_owned(std::size_t table_id) const override;

  void free(std::size_t table_id) override;

  std::optional<std::size_t> get_tableId_by_userId(std::size_t user_id) const override;

  std::vector<std::size_t> get_all_occupied_tables() const override;

  std::size_t count_occupied_tables() const override;

  bool all_free() const override;

private:
  std::unordered_map<std::size_t, std::size_t> M_table_to_user_; // TableId -> UserId
  std::unordered_map<std::size_t, std::size_t> M_user_to_table; // UserId -> TableId
};

} // namespace club
