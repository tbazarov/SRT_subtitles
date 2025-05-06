#pragma once

#include <string>
#include <iostream>

class Time {
public:
    Time();
    Time(int hours, int minutes, int seconds, int milliseconds);
    explicit Time(const std::string& timeStr);
    
    bool isValid() const;
    int toMilliseconds() const;
    
    bool operator<(const Time& other) const;
    bool operator==(const Time& other) const;
    bool operator<=(const Time& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
    
private:
    int hours;
    int minutes;
    int seconds;
    int milliseconds;
    
    bool parseFromString(const std::string& timeStr);
};
