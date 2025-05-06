#pragma once

#include "Repository.h"

#include <gtest/gtest.h>

class ClientRepositoryTest : public ::testing::Test {
protected:
  void SetUp() override {
    repo.save(club::User("Alice", 1));
    repo.save(club::User("Bob", 2));
  }

  club::InMemoryClientRepository repo;
};

class TableOwnerRepository : public ::testing::Test {
protected:
  void SetUp() override {
    repo.assign(1, 2);
    repo.assign(2, 4);
  }

  club::InMemoryTableOwnerRepository repo;
};

class WorkRepository : public ::testing::Test {
protected:
  void SetUp() override {
    M_user_repo.save(club::User("Alice", 1));
    M_user_repo.save(club::User("Bob", 2));
    M_table_repo.assign(3, 1);
    M_table_repo.assign(4, 2);
  }

  club::InMemoryClientRepository M_user_repo;
  club::InMemoryTableOwnerRepository M_table_repo;
};
