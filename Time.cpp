#include "Time.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

Time::Time() : hours(0), minutes(0), seconds(0), milliseconds(0) {}

Time::Time(int hours, int minutes, int seconds, int milliseconds)
    : hours(hours), minutes(minutes), seconds(seconds), milliseconds(milliseconds) {}

Time::Time(const std::string& timeStr) {
    if (!parseFromString(timeStr)) {
        throw std::invalid_argument("Invalid time format: " + timeStr);
    }
}

bool Time::parseFromString(const std::string& timeStr) {
    char sep1, sep2, sep3, sep4;
    std::istringstream iss(timeStr);
    
    iss >> hours >> sep1 >> minutes >> sep2 >> seconds >> sep3 >> milliseconds;
    
    if (iss.fail() || sep1 != ':' || sep2 != ':' || sep3 != ',') {
        return false;
    }
    
    return hours >= 0 && minutes >= 0 && minutes < 60 && 
           seconds >= 0 && seconds < 60 && milliseconds >= 0 && milliseconds < 1000;
}

bool Time::isValid() const {
    return hours >= 0 && minutes >= 0 && minutes < 60 && 
           seconds >= 0 && seconds < 60 && milliseconds >= 0 && milliseconds < 1000;
}

int Time::toMilliseconds() const {
    return hours * 3600000 + minutes * 60000 + seconds * 1000 + milliseconds;
}

bool Time::operator<(const Time& other) const {
    return toMilliseconds() < other.toMilliseconds();
}

bool Time::operator==(const Time& other) const {
    return toMilliseconds() == other.toMilliseconds();
}

bool Time::operator<=(const Time& other) const {
    return *this < other || *this == other;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << std::setfill('0') << std::setw(2) << time.hours << ":"
       << std::setw(2) << time.minutes << ":" << std::setw(2) << time.seconds
       << "," << std::setw(3) << time.milliseconds;
    return os;
}