#pragma once

#include "Subtitle.h"
#include <vector>
#include <string>
#include <iostream>

class SubtitleParser {
public:
    static std::vector<Subtitle> parseFromFile(const std::string& filename);
    static std::vector<Subtitle> parseFromStream(std::istream& input);
    
private:
    static bool parseSubtitleBlock(std::istream& input, Subtitle& subtitle);
    static void trim(std::string& str);
};
