#include "Club.h"

#include "test_classes.h"

#include <Utils.h>

#include <ranges>

TEST(ClubTest, left) {
std:
  size_t tables = 5, price = 100;
  club::Time start{"11:00"};
  club::Time end{"13:00"};

  ComputerClub club{tables, price, start, end};
}

TEST(ClubTest, WorkFine) {
  std::string input = "3\n09:00 19:00"
                      "\n10"
                      "\n08:48 1 client1"
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

  std::string t_table, t_price, t_time;
  std::getline(iss, t_table);
  std::getline(iss, t_time);
  std::getline(iss, t_price);

  auto times = club::split(t_time);
  std::string t_start = times[0];
  std::string t_end = times[1];
  auto comp = ComputerClub(std::stoi(t_table), std::stoi(t_price), club::Time{t_start}, club::Time{t_end});

  std::string event_token;
  while (std::getline(iss, event_token)) {
    auto ev = club::event_parse(event_token);
    comp.handle_event(ev);
  }
}

TEST(ClubTest, NoThrowFromInput) {
  std::string input = "3\n09:00 19:00"
                      "\n10"
                      "\n08:48 1 client1"
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

  std::string t_table, t_price, t_time;
  std::getline(iss, t_table);
  std::getline(iss, t_time);
  std::getline(iss, t_price);

  auto times = club::split(t_time);
  std::string t_start = times[0];
  std::string t_end = times[1];
  auto comp = ComputerClub(std::stoi(t_table), std::stoi(t_price), club::Time{t_start}, club::Time{t_end});

  std::string event_token;
  while (std::getline(iss, event_token)) {
    auto ev = club::event_parse(event_token);
    comp.handle_event(ev);
  }
}
