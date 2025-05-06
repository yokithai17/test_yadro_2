#include "test_classes.h"

#include <Utils.h>

TEST(Event, create_test) {
  EXPECT_NO_THROW(club::event_parse("08:48 1 client1"));
  EXPECT_NO_THROW(club::event_parse("08:48 2 client1 2"));
  EXPECT_THROW(club::event_parse("00:11"), club::parse_exception);
  EXPECT_THROW(club::event_parse("3213"), club::parse_exception);
  EXPECT_TRUE(club::event_parse("08:48 1 client1").get_type() == club::EventType::Arrived);
  EXPECT_TRUE(club::event_parse("08:48 1 client1").get_time() == club::Time(8, 48));
}

TEST(Event, event_parse_test) {
  std::string input = "08:48 1 client1"
                      "\n09:41 1 client1"
                      "\n09:48 1 client2"
                      "\n09:52 3 client1"
                      "\n09:54 2 client1 1"
                      "\n10:25 2 client2 2"
                      "\n10:58 1 client3"
                      "\n10:59 2 client3 3"
                      "\n11:30 1 client4"
                      "\n11:35 2 client4 2"
                      "\n11:45 3 client4"
                      "\n12:33 4 client1"
                      "\n12:43 4 client2"
                      "\n15:52 4 client4";
  std::istringstream iss(input);
  std::string token;
  while (std::getline(iss, token)) {
    auto ev = club::event_parse(token);
  }
}
