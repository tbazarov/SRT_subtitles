#include "Time.h"
#include "Subtitle.h"
#include "SubtitleParser.h"
#include "SubtitleProcessor.h"
#include <gtest/gtest.h>
#include <sstream>

// Time tests
TEST(TimeTest, ConstructorAndValidation) {
    Time t1(1, 2, 3, 4);
    ASSERT_EQ(t1.isValid(), true);
    
    Time t2(25, 0, 0, 0);
    ASSERT_EQ(t2.isValid(), false);
}

TEST(TimeTest, ParseFromString) {
    Time t1("00:00:01,000");
    ASSERT_EQ(t1.isValid(), true);
    ASSERT_EQ(t1.toMilliseconds(), 1000);
}

// Subtitle tests
TEST(SubtitleTest, ConstructorAndValidation) {
    Time start("00:00:01,000");
    Time end("00:00:02,000");
    std::vector<std::string> text = {"Test"};
    
    Subtitle s1(1, start, end, text);
    ASSERT_EQ(s1.isValid(), true);
    ASSERT_EQ(s1.getNumber(), 1);
}

// SubtitleParser tests
TEST(SubtitleParserTest, ParseValidSubtitle) {
    std::stringstream input(
        "1\n"
        "00:00:01,000 --> 00:00:02,000\n"
        "Test subtitle\n"
        "\n"
    );
    
    auto subtitles = SubtitleParser::parseFromStream(input);
    ASSERT_EQ(subtitles.size(), 1);
    
    const auto& sub = subtitles[0];
    ASSERT_EQ(sub.getNumber(), 1);
    ASSERT_EQ(sub.getStartTime().toMilliseconds(), 1000);
    ASSERT_EQ(sub.getEndTime().toMilliseconds(), 2000);
    ASSERT_EQ(sub.getText().size(), 1);
    ASSERT_EQ(sub.getText()[0], "Test subtitle");
}

TEST(SubtitleParserTest, ParseMultipleSubtitles) {
    std::stringstream input(
        "1\n"
        "00:00:01,000 --> 00:00:02,000\n"
        "First\n"
        "\n"
        "2\n"
        "00:00:02,000 --> 00:00:03,000\n"
        "Second\n"
        "\n"
    );
    
    auto subtitles = SubtitleParser::parseFromStream(input);
    ASSERT_EQ(subtitles.size(), 2);
    
    ASSERT_EQ(subtitles[0].getNumber(), 1);
    ASSERT_EQ(subtitles[1].getNumber(), 2);
}

TEST(SubtitleParserTest, ParseInvalidSubtitle) {
    std::stringstream input(
        "1\n"
        "invalid time format\n"
        "Test subtitle\n"
        "\n"
    );
    
    auto subtitles = SubtitleParser::parseFromStream(input);
    ASSERT_EQ(subtitles.size(), 0);
}

// SubtitleProcessor tests
TEST(SubtitleProcessorTest, ProcessSingleSubtitle) {
    std::vector<Subtitle> subtitles = {
        {1, Time("00:00:01,000"), Time("00:00:02,000"), {"Test"}}
    };
    
    auto commands = SubtitleProcessor::processSubtitles(subtitles);
    ASSERT_EQ(commands.size(), 2);
    
    ASSERT_NE(commands[0].find("SHOW TEXT \"Test\""), std::string::npos);
    ASSERT_NE(commands[1].find("HIDE TEXT"), std::string::npos);
}

TEST(SubtitleProcessorTest, ProcessOverlappingSubtitles) {
    std::vector<Subtitle> subtitles = {
        {1, Time("00:00:01,000"), Time("00:00:03,000"), {"First"}},
        {2, Time("00:00:02,000"), Time("00:00:04,000"), {"Second"}}
    };
    
    auto commands = SubtitleProcessor::processSubtitles(subtitles);
    ASSERT_EQ(commands.size(), 4);
    
    ASSERT_NE(commands[1].find("SHOW TEXT \"First Second\""), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}