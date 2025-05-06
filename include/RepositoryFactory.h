#pragma once
#include "IRepository.h"
#include "Repository.h"

#include <memory>

namespace club {
// Фабрика для создания репозиториев
struct RepositoryFactory {
  static std::unique_ptr<IClientRepository> createClientRepository() {
    return std::make_unique<InMemoryClientRepository>();
  }

  static std::unique_ptr<ITableOwnerRepository> createTableOwnerRepository() {
    return std::make_unique<InMemoryTableOwnerRepository>();
  }

  static std::unique_ptr<ITableRepository> createTableRepository(std::size_t tables) {
    return std::make_unique<InMemoryTableRepository>(tables);
  }
};
} // namespace club