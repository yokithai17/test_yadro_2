#pragma once

#include "Repository.h"

#include <gtest/gtest.h>

class ClientRepositoryTest : public ::testing::Test {
protected:
  void SetUp() override {
    repo.save_client(club::User("Alice", 1));
    repo.save_client(club::User("Bob", 2));
  }

  club::ClientRepository repo;
};

class TableOwnerRepository : public ::testing::Test {
protected:
  void SetUp() override {
    repo.assign_table(1, 2);
    repo.assign_table(2, 4);
  }

  club::TableOwnerRepository repo;
};

class WorkRepository : public ::testing::Test {
protected:
  void SetUp() override {
    M_user_repo.save_client(club::User("Alice", 1));
    M_user_repo.save_client(club::User("Bob", 2));
    M_table_repo.assign_table(3, 1);
    M_table_repo.assign_table(4, 2);
  }

  club::ClientRepository M_user_repo;
  club::TableOwnerRepository M_table_repo;
};
