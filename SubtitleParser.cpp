#include "SubtitleParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<Subtitle> SubtitleParser::parseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    return parseFromStream(file);
}

std::vector<Subtitle> SubtitleParser::parseFromStream(std::istream& input) {
    std::vector<Subtitle> subtitles;
    Subtitle subtitle(0, Time(), Time(), {});
    
    while (parseSubtitleBlock(input, subtitle)) {
        if (subtitle.isValid()) {
            subtitles.push_back(subtitle);
        }
    }
    
    return subtitles;
}

bool SubtitleParser::parseSubtitleBlock(std::istream& input, Subtitle& subtitle) {
    std::string line;
    
    // Read number
    while (std::getline(input, line)) {
        trim(line);
        if (!line.empty()) break;
    }
    if (line.empty()) return false;
    
    int number;
    try {
        number = std::stoi(line);
    } catch (...) {
        return false;
    }
    
    // Read time range
    std::getline(input, line);
    trim(line);
    
    size_t arrowPos = line.find("-->");
    if (arrowPos == std::string::npos) {
        return false;
    }
    
    std::string startStr = line.substr(0, arrowPos);
    std::string endStr = line.substr(arrowPos + 3);
    trim(startStr);
    trim(endStr);
    
    Time start, end;
    try {
        start = Time(startStr);
        end = Time(endStr);
    } catch (...) {
        return false;
    }
    
    // Read text
    std::vector<std::string> text;
    while (std::getline(input, line)) {
        trim(line);
        if (line.empty()) break;
        text.push_back(line);
    }
    
    subtitle = Subtitle(number, start, end, text);
    return true;
}

void SubtitleParser::trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}