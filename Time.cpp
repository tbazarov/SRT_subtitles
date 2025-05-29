#include "Time.h"
#include <sstream>
#include <iomanip>

Time::Time(unsigned int hours, unsigned int minutes, unsigned int seconds, unsigned int milliseconds)
    : hours(hours), minutes(minutes), seconds(seconds), milliseconds(milliseconds)
{
    validate();
}

void Time::validate() {
    if (minutes >= 60 || seconds >= 60 || milliseconds >= 1000) {
        std::ostringstream oss;
        oss << "Invalid time: "
            << *this
            << ". Minutes must be in [0,59], seconds in [0,59], milliseconds in [0,999].";
        throw std::invalid_argument(oss.str());
    }
}

int Time::toMilliseconds() const {
    return static_cast<int>(
        hours * 3600000ULL +
        minutes * 60000ULL +
        seconds * 1000ULL +
        milliseconds
    );
}

bool Time::operator<(const Time& other) const {
    return toMilliseconds() < other.toMilliseconds();
}

bool Time::operator==(const Time& other) const {
    return toMilliseconds() == other.toMilliseconds();
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::operator<=(const Time& other) const {
    return !(other < *this);
}

bool Time::operator>(const Time& other) const {
    return other < *this;
}

bool Time::operator>=(const Time& other) const {
    return !(*this < other);
}