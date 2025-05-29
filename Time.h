#pragma once

#include <string>
#include <ostream>

class Time {
public:
    explicit Time(unsigned int hours = 0,
                  unsigned int minutes = 0,
                  unsigned int seconds = 0,
                  unsigned int milliseconds = 0);

    int toMilliseconds() const;

    bool operator<(const Time& other) const;
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator>=(const Time& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Time& time);

private:
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds; 
    unsigned int milliseconds; 

    void validate();
};