#include "Repository.h"

#include "Event.h"

// Client Repository
void club::InMemoryClientRepository::save(const club::User& client) {
  M_storage_.insert(client);
}

bool club::InMemoryClientRepository::contains(const std::string& name) const {
  return M_storage_.contains(User(name));
}

void club::InMemoryClientRepository::remove(const std::string& name) {
  M_storage_.erase(User(name));
}

std::optional<std::string> club::InMemoryClientRepository::get_name_by_id(std::size_t id) const {
  for (auto it = M_storage_.begin(); it != M_storage_.end(); ++it) {
    if (it->id() == id) {
      return it->name();
    }
  }
  return std::nullopt;
}

std::optional<std::size_t> club::InMemoryClientRepository::find_id(const std::string& name) const {
  if (auto it = M_storage_.find(name); it != M_storage_.end()) {
    return std::make_optional(it->id());
  }
  return std::nullopt;
}

std::optional<std::size_t> club::InMemoryClientRepository::get_client_id(const std::string& name) const {
  return find_id(name);
}

std::vector<club::User> club::InMemoryClientRepository::last_users() const {
  std::vector<User> ret;
  for (const auto& user : M_storage_) {
    ret.push_back(user);
  }
  return ret;
}


// Table Repository
void club::InMemoryTableOwnerRepository::assign(std::size_t table_id, std::size_t client_id) {
  M_table_to_user_[table_id] = client_id;
  M_user_to_table[client_id] = table_id;
}

std::pair<bool, std::size_t> club::InMemoryTableOwnerRepository::table_owned(std::size_t table_id) const {
  if (auto it = M_table_to_user_.find(table_id); it != M_table_to_user_.end()) {
    return std::make_pair(true, it->second);
  }
  return std::make_pair(false, 0);
}

void club::InMemoryTableOwnerRepository::free(std::size_t table_id) {
  if (auto it = M_table_to_user_.find(table_id); it != M_table_to_user_.end()) {
    M_table_to_user_.erase(it);
    M_user_to_table.erase(it->second);
  }
}

std::optional<std::size_t>club::InMemoryTableOwnerRepository::get_tableId_by_userId(std::size_t user_id) const {
  if (auto it = M_user_to_table.find(user_id); it != M_user_to_table.end()) {
    return std::make_optional(it->second);
  }
  return std::nullopt;
}

std::vector<std::size_t> club::InMemoryTableOwnerRepository::get_all_occupied_tables() const {
  std::vector<std::size_t> result;
  for (const auto& [table_id, _] : M_table_to_user_) {
    result.push_back(table_id);
  }
  return result;
}

std::size_t club::InMemoryTableOwnerRepository::count_occupied_tables() const {
  return M_user_to_table.size();
}

bool club::InMemoryTableOwnerRepository::all_free() const {
  return M_user_to_table.empty() && M_table_to_user_.empty();
}
