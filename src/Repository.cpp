#include "Repository.h"

#include "Event.h"

// Client Repository
void club::ClientRepository::save_client(const club::User& client) {
  M_storage_.insert(client);
}

bool club::ClientRepository::contains_client(const std::string& name) const {
  return M_storage_.contains(User(name));
}

void club::ClientRepository::remove_client(const std::string& name) {
  M_storage_.erase(User(name));
}

std::string club::ClientRepository::get_name_by_id(std::size_t id) const {
  for (auto it = M_storage_.begin(); it != M_storage_.end(); ++it) {
    if (it->id() == id) {
      return it->name();
    }
  }
  return "nothing";
}

std::pair<bool, std::size_t> club::ClientRepository::find_client_id(const std::string& name) const {
  if (auto it = M_storage_.find(name); it != M_storage_.end()) {
    return std::make_pair(true, it->id());
  }
  return std::make_pair(false, 0);
}

std::size_t club::ClientRepository::get_client_id(const std::string& name) const {
  return find_client_id(name).second;
}

// Table Repository
void club::TableOwnerRepository::assign_table(std::size_t table_id, std::size_t client_id) {
  M_table_to_user_[table_id] = client_id;
  M_user_to_table[client_id] = table_id;
}

std::pair<bool, std::size_t> club::TableOwnerRepository::is_table_owned(std::size_t table_id) const {
  if (auto it = M_table_to_user_.find(table_id); it != M_table_to_user_.end()) {
    return std::make_pair(true, it->second);
  }
  return std::make_pair(false, 0);
}

void club::TableOwnerRepository::free_table(std::size_t table_id) {
  if (auto it = M_table_to_user_.find(table_id); it != M_table_to_user_.end()) {
    M_table_to_user_.erase(it);
    M_user_to_table.erase(it->second);
  }
}

std::size_t club::TableOwnerRepository::get_tableId_by_userId(std::size_t user_id) const {
  return M_user_to_table.at(user_id);
}

std::vector<std::size_t> club::TableOwnerRepository::get_all_occupied_tables() const {
  std::vector<std::size_t> result;
  for (const auto& [table_id, _] : M_table_to_user_) {
    result.push_back(table_id);
  }
  return result;
}

std::size_t club::TableOwnerRepository::count_occupied_tables() const {
  return M_user_to_table.size();
}

bool club::TableOwnerRepository::all_free() const {
  return M_user_to_table.empty() && M_table_to_user_.empty();
}
