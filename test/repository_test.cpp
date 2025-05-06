#include "test_classes.h"

#include <gtest/gtest.h>

TEST_F(ClientRepositoryTest, SaveAndContains) {
  EXPECT_TRUE(repo.contains_client("Alice"));
  EXPECT_TRUE(repo.contains_client("Bob"));
  EXPECT_FALSE(repo.contains_client("Charlie"));
}

TEST_F(ClientRepositoryTest, GetClientId) {
  EXPECT_EQ(repo.get_client_id("Alice"), 1);
  EXPECT_EQ(repo.get_client_id("Bob"), 2);
  EXPECT_EQ(repo.get_client_id("Charlie"), 0); // Несуществующий клиент
}

TEST_F(ClientRepositoryTest, FindClientId) {
  auto [found1, id1] = repo.find_client_id("Alice");
  EXPECT_TRUE(found1);
  EXPECT_EQ(id1, 1);

  auto [found2, id2] = repo.find_client_id("Charlie");
  EXPECT_FALSE(found2);
  EXPECT_EQ(id2, 0);
}

TEST_F(ClientRepositoryTest, GetNameById) {
  EXPECT_EQ(repo.get_name_by_id(1), "Alice");
  EXPECT_EQ(repo.get_name_by_id(2), "Bob");
  EXPECT_EQ(repo.get_name_by_id(3), "nothing"); // Несуществующий ID
}

TEST_F(ClientRepositoryTest, RemoveClient) {
  repo.remove_client("Alice");
  EXPECT_FALSE(repo.contains_client("Alice"));
  EXPECT_TRUE(repo.contains_client("Bob"));
}

TEST_F(TableOwnerRepository, TableOwned) {
  EXPECT_TRUE(repo.is_table_owned(1).first);
  EXPECT_FALSE(repo.is_table_owned(3).first);
  EXPECT_TRUE(repo.is_table_owned(2).first);
}

TEST_F(TableOwnerRepository, FreeTable) {
  EXPECT_NO_THROW(repo.free_table(1));
  EXPECT_FALSE(repo.is_table_owned(1).first);
  EXPECT_NO_THROW(repo.free_table(1));
}

TEST_F(TableOwnerRepository, AssignTable) {
  EXPECT_NO_THROW(repo.assign_table(5, 3));
  EXPECT_TRUE(repo.is_table_owned(5).first);
  EXPECT_NO_THROW(repo.assign_table(6, 7));
  EXPECT_TRUE(repo.is_table_owned(6).first);
}

TEST_F(TableOwnerRepository, GetTableID) {
  EXPECT_EQ(repo.get_tableId_by_userId(2), 1);
  EXPECT_EQ(repo.get_tableId_by_userId(4), 2);
}

TEST_F(TableOwnerRepository, CountOccupiedTables) {
  EXPECT_EQ(repo.count_occupied_tables(), 2);
  repo.assign_table(5, 3);
  EXPECT_EQ(repo.count_occupied_tables(), 3);
}
