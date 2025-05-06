#pragma once
#include "User.h"
#include <optional>
#include <vector>
#include <string>

namespace club {
class IClientRepository {
public:
  virtual ~IClientRepository() = default;

  virtual void save(const User& client) = 0;
  virtual bool contains(const std::string& name) const = 0;
  virtual void remove(const std::string& name) = 0;
  virtual std::optional<std::string> get_name_by_id(std::size_t id) const = 0;
  virtual std::optional<std::size_t> find_id(const std::string& name) const = 0;
  virtual std::vector<User> last_users() const = 0;
};

class ITableOwnerRepository {
public:
  virtual ~ITableOwnerRepository() = default;

  virtual void assign(std::size_t table_id, std::size_t client_id) = 0;
  virtual void free(std::size_t table_id) = 0;
  virtual std::pair<bool, std::size_t> table_owned(std::size_t table_id) const = 0;
  virtual std::optional<std::size_t> get_tableId_by_userId(std::size_t client_id) const = 0;
  //virtual std::optional<std::size_t> get_client_id(const std::string& name) const = 0;
  virtual std::vector<std::size_t> get_all_occupied_tables() const = 0;
  virtual std::size_t count_occupied_tables() const = 0;
  virtual bool all_free() const = 0;
};
class ITableRepository {
  public:
  virtual ~ITableRepository() = default;

  virtual void add_gain(std::size_t table_id, std::size_t gain) noexcept = 0;
  virtual void add_working_time(std::size_t table_id, Time time) noexcept = 0;
  virtual void add_starttime(std::size_t table_id, Time time) noexcept = 0;
  virtual Time get_start_time(std::size_t table_id) const noexcept = 0;
  virtual Table get_table(int table_id) const noexcept = 0;
};
} // namespace club