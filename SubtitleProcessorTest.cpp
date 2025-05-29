#include <gtest/gtest.h>
#include "Time.h"
#include "Subtitle.h"
#include "SubtitleProcessor.h"

#include <vector>

// Тест: один субтитр — показ и скрытие
TEST(SubtitleProcessorTest, SingleSubtitle) {
    Subtitle sub1(1, Time(0, 0, 1, 0), Time(0, 0, 3, 0), {"Hello"});
    
    SubtitleProcessor processor;
    std::vector<std::string> result = processor.processSubtitles({sub1});
    
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "00:00:01,000 SHOW TEXT \"Hello\"");
    EXPECT_EQ(result[1], "00:00:03,000 HIDE TEXT");
}

// Тест: два непересекающихся субтитра — последовательная отрисовка
TEST(SubtitleProcessorTest, NonOverlappingSubtitles) {
    Subtitle sub1(1, Time(0, 0, 1, 0), Time(0, 0, 2, 0), {"A"});
    Subtitle sub2(2, Time(0, 0, 3, 0), Time(0, 0, 4, 0), {"B"});

    SubtitleProcessor processor;
    std::vector<std::string> result = processor.processSubtitles({sub1, sub2});

    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "00:00:01,000 SHOW TEXT \"A\"");
    EXPECT_EQ(result[1], "00:00:02,000 HIDE TEXT");
    EXPECT_EQ(result[2], "00:00:03,000 SHOW TEXT \"B\"");
    EXPECT_EQ(result[3], "00:00:04,000 HIDE TEXT");
}

// Тест: два пересекающихся субтитра — должен объединиться вывод
TEST(SubtitleProcessorTest, OverlappingSubtitles) {
    Subtitle sub1(1, Time(0, 0, 1, 0), Time(0, 0, 4, 0), {"Hello"});
    Subtitle sub2(2, Time(0, 0, 2, 0), Time(0, 0, 3, 0), {"World"});

    SubtitleProcessor processor;
    std::vector<std::string> result = processor.processSubtitles({sub1, sub2});

    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "00:00:01,000 SHOW TEXT \"Hello\"");
    EXPECT_EQ(result[1], "00:00:02,000 SHOW TEXT \"Hello World\"");
    EXPECT_EQ(result[2], "00:00:03,000 HIDE TEXT");
    EXPECT_EQ(result[3], "00:00:04,000 HIDE TEXT");
}

// Тест: несколько строк текста в одном субтитре
TEST(SubtitleProcessorTest, MultiLineText) {
    Subtitle sub(1, Time(0, 0, 1, 0), Time(0, 0, 2, 0), {"First line", "Second line"});

    SubtitleProcessor processor;
    std::vector<std::string> result = processor.processSubtitles({sub});

    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "00:00:01,000 SHOW TEXT \"First line Second line\"");
    EXPECT_EQ(result[1], "00:00:02,000 HIDE TEXT");
}