#pragma once

#include "Subtitle.h"
#include <vector>
#include <string>
#include <iostream>
#include <optional>

class SubtitleParser {
public:
    SubtitleParser() = delete;
    ~SubtitleParser() = delete;
    static std::vector<Subtitle> parseFromFile(const std::string& filename);
    static std::vector<Subtitle> parseFromStream(std::istream& input);

private:
    
    static bool parseSubtitleBlock(std::istream& input, Subtitle& subtitle);
    static bool readNumber(std::istream& input, int& number);
    static bool readTimeRange(std::istream& input, Time& start, Time& end);
    static bool readText(std::istream& input, std::vector<std::string>& text);
    static void trim(std::string& str);
    static Time parseTime(const std:: string& timeStr);
};