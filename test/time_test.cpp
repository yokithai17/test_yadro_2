#include "Time.h"

#include "test_classes.h"

TEST(TimeTest, Test1) {
  using club::Time;
  Time tm = Time("12:01");
  EXPECT_TRUE(tm.get_hour() == 12 && tm.get_minute() == 1);
  EXPECT_TRUE(static_cast<std::string>(tm) == "12:01");
}

TEST(TimeTest, difftime) {
  using club::Time;
  Time lhs = Time("12:33");
  Time rhs = Time("09:54");
  EXPECT_EQ((lhs - rhs).get_hour(), 2);
  EXPECT_EQ((lhs - rhs).get_minute(), 39);
  EXPECT_EQ(lhs - rhs, Time(2, 39)); // 3

  Time t1 = Time(12, 33);
  Time t2 = Time(15, 52);
  EXPECT_EQ((t2 - t1).get_hour(), 3);
  EXPECT_EQ((t2 - t1).get_minute(), 19);
  EXPECT_EQ(t2 - t1, Time(3, 19)); // 4

  EXPECT_EQ((t2 - rhs), Time(5, 58));
}
