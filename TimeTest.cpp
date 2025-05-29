#include <gtest/gtest.h>
#include "Time.h"

TEST(TimeTest, CompareTimes) {
    Time t1(1, 2, 3, 450);
    Time t2(1, 2, 3, 451);

    EXPECT_TRUE(t1 < t2);
    EXPECT_TRUE(t2 > t1);
    EXPECT_TRUE(t1 <= t2);
    EXPECT_TRUE(t2 >= t1);
}

TEST(TimeTest, ToMilliseconds) {
    Time t(1, 1, 1, 500);
    EXPECT_EQ(t.toMilliseconds(), 3661500); // 1ч = 3600000 + 1мин=60000 + 1сек=1000 + 500
}