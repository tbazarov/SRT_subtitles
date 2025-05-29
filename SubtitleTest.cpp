#include <gtest/gtest.h>
#include "Subtitle.h"
#include "Time.h"

TEST(SubtitleTest, StartTimeLessThanEndTime) {
    Time start(0, 1, 2, 300);
    Time end(0, 1, 3, 300);

    Subtitle sub(1, start, end, {"Hello"});
    EXPECT_EQ(sub.getStartTime(), start);
    EXPECT_EQ(sub.getEndTime(), end);
}

TEST(SubtitleTest, InvalidTimeRangeThrows) {
    Time start(0, 1, 2, 300);
    Time end(0, 1, 1, 300);

    EXPECT_THROW((Subtitle(1, start, end, {"Text"})), std::invalid_argument);
}