#include "Subtitle.h"
#include <stdexcept>

Subtitle::Subtitle(int number, const Time& start, const Time& end, const std::vector<std::string>& text)
    : number(number), startTime(start), endTime(end), textLines(text)
{
    if (start > end) {
        throw std::invalid_argument("Start time must be <= end time");
    }
}

int Subtitle::getNumber() const {
    return number;
}

const Time& Subtitle::getStartTime() const {
    return startTime;
}

const Time& Subtitle::getEndTime() const {
    return endTime;
}

const std::vector<std::string>& Subtitle::getText() const {
    return textLines;
}

bool Subtitle::isValid() const {
    return startTime <= endTime;
}