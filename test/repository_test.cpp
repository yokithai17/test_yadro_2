#include "test_classes.h"

#include <gtest/gtest.h>

TEST_F(ClientRepositoryTest, SaveAndContains) {
  EXPECT_TRUE(repo.contains("Alice"));
  EXPECT_TRUE(repo.contains("Bob"));
  EXPECT_FALSE(repo.contains("Charlie"));
}

TEST_F(ClientRepositoryTest, GetClientId) {
  EXPECT_EQ(repo.get_client_id("Alice"), 1);
  EXPECT_EQ(repo.get_client_id("Bob"), 2);
  EXPECT_EQ(repo.get_client_id("Charlie"), std::nullopt); // Несуществующий клиент
}

TEST_F(ClientRepositoryTest, FindClientId) {
  auto x = repo.find_id("Alice");
  EXPECT_TRUE(x.has_value());
  EXPECT_EQ(x.value(), 1);

  auto y = repo.find_id("Charlie");
  EXPECT_FALSE(y.has_value());
}

TEST_F(ClientRepositoryTest, GetNameById) {
  EXPECT_EQ(repo.get_name_by_id(1), "Alice");
  EXPECT_EQ(repo.get_name_by_id(2), "Bob");
  EXPECT_EQ(repo.get_name_by_id(3), std::nullopt); // Несуществующий ID
}

TEST_F(ClientRepositoryTest, RemoveClient) {
  repo.remove("Alice");
  EXPECT_FALSE(repo.contains("Alice"));
  EXPECT_TRUE(repo.contains("Bob"));
}

TEST_F(TableOwnerRepository, TableOwned) {
  EXPECT_TRUE(repo.table_owned(1).first);
  EXPECT_FALSE(repo.table_owned(3).first);
  EXPECT_TRUE(repo.table_owned(2).first);
}

TEST_F(TableOwnerRepository, FreeTable) {
  EXPECT_NO_THROW(repo.free(1));
  EXPECT_FALSE(repo.table_owned(1).first);
  EXPECT_NO_THROW(repo.free(1));
}

TEST_F(TableOwnerRepository, AssignTable) {
  EXPECT_NO_THROW(repo.assign(5, 3));
  EXPECT_TRUE(repo.table_owned(5).first);
  EXPECT_NO_THROW(repo.assign(6, 7));
  EXPECT_TRUE(repo.table_owned(6).first);
}

TEST_F(TableOwnerRepository, GetTableID) {
  EXPECT_EQ(repo.get_tableId_by_userId(2), 1);
  EXPECT_EQ(repo.get_tableId_by_userId(4), 2);
}

TEST_F(TableOwnerRepository, CountOccupiedTables) {
  EXPECT_EQ(repo.count_occupied_tables(), 2);
  repo.assign(5, 3);
  EXPECT_EQ(repo.count_occupied_tables(), 3);
}
