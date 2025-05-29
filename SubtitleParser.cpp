#include "SubtitleParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

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
        subtitles.push_back(subtitle); // Теперь объект всегда валиден
    }

    return subtitles;
}

bool SubtitleParser::parseSubtitleBlock(std::istream& input, Subtitle& subtitle) {
    int number;
    if (!readNumber(input, number)) {
        return false;
    }

    Time start, end;
    if (!readTimeRange(input, start, end)) {
        return false;
    }

    std::vector<std::string> text;
    if (!readText(input, text)) {
        return false;
    }

    subtitle = Subtitle(number, start, end, text);
    return true;
}

bool SubtitleParser::readNumber(std::istream& input, int& number) {
    std::string line;
    while (std::getline(input, line)) {
        trim(line);
        if (!line.empty()) break;
    }
    if (line.empty()) return false;

    try {
        number = std::stoi(line);
        return true;
    } catch (...) {
        return false;
    }
}

bool SubtitleParser::readTimeRange(std::istream& input, Time& start, Time& end) {
    std::string line;
    if (!std::getline(input, line)) {
        return false;
    }

    trim(line);
    size_t arrowPos = line.find("-->");
    if (arrowPos == std::string::npos) {
        return false;
    }

    std::string startStr = line.substr(0, arrowPos);
    std::string endStr = line.substr(arrowPos + 3);
    trim(startStr);
    trim(endStr);

    try {
        start = parseTime(startStr);
        end = parseTime(endStr);
        return true;
    } catch (...) {
        return false;
    }
}

bool SubtitleParser::readText(std::istream& input, std::vector<std::string>& text) {
    std::string line;
    while (std::getline(input, line)) {
        trim(line);
        if (line.empty()) break;
        text.push_back(line);
    }
    return !text.empty(); // Требуем хотя бы одну строку текста
}

Time SubtitleParser::parseTime(const std::string& timeStr) {
    char sep1, sep2, sep3;
    unsigned int hours, minutes, seconds, milliseconds;

    std::istringstream iss(timeStr);
    iss >> hours >> sep1 >> minutes >> sep2 >> seconds >> sep3 >> milliseconds;

    if (iss.fail() || sep1 != ':' || sep2 != ':' || sep3 != ',') {
        throw std::invalid_argument("Invalid time format: " + timeStr);
    }

    if (minutes >= 60 || seconds >= 60 || milliseconds >= 1000) {
        throw std::invalid_argument("Invalid time values: " + timeStr);
    }

    return Time(hours, minutes, seconds, milliseconds);
}

void SubtitleParser::trim(std::string& str) {
    auto not_space = [](char ch) { return !std::isspace(static_cast<unsigned char>(ch)); };
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), not_space));
    str.erase(std::find_if(str.rbegin(), str.rend(), not_space).base(), str.end());
}