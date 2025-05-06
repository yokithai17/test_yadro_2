#include "test_classes.h"

TEST(random_test, test1) {
  using club::User;
  club::ClientRepository cl_repo;
  club::TableOwnerRepository tr_repo;
  cl_repo.save_client(User("client1", 1));
  cl_repo.save_client(User("client2", 2));
}
