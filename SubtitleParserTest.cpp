#include <gtest/gtest.h>
#include "SubtitleParser.h"
#include "Subtitle.h"
#include "Time.h"
#include <sstream>

TEST(SubtitleParserTest, ParseSingleBlock) {
    std::istringstream input(
        "1\n"
        "00:00:01,000 --> 00:00:04,000\n"
        "This is a test subtitle.\n"
    );

    Subtitle subtitle(0, Time(), Time(), {});
    bool success = SubtitleParser::parseSubtitleBlock(input, subtitle);

    EXPECT_TRUE(success);
    EXPECT_EQ(subtitle.getNumber(), 1);
    EXPECT_EQ(subtitle.getStartTime(), Time(0, 0, 1, 0));
    EXPECT_EQ(subtitle.getEndTime(), Time(0, 0, 4, 0));
    ASSERT_EQ(subtitle.getText().size(), 1);
    EXPECT_EQ(subtitle.getText()[0], "This is a test subtitle.");
}