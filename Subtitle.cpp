#include "Subtitle.h"

Subtitle::Subtitle(int number, const Time& start, const Time& end, const std::vector<std::string>& text)
    : number(number), startTime(start), endTime(end), text(text) {}

int Subtitle::getNumber() const {
    return number;
}

Time Subtitle::getStartTime() const {
    return startTime;
}

Time Subtitle::getEndTime() const {
    return endTime;
}

const std::vector<std::string>& Subtitle::getText() const {
    return text;
}

bool Subtitle::isValid() const {
    return startTime.isValid() && endTime.isValid() && startTime <= endTime && !text.empty();
}