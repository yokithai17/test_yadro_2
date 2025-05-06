#include "test_classes.h"

TEST(random_test, test1) {
  using club::User;
  club::InMemoryClientRepository cl_repo;
  club::InMemoryTableOwnerRepository tr_repo;
  cl_repo.save(User("client1", 1));
  cl_repo.save(User("client2", 2));
}
