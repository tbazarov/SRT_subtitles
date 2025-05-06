#pragma once

#include "Time.h"
#include <string>
#include <vector>

class Subtitle {
public:
    Subtitle(int number, const Time& start, const Time& end, const std::vector<std::string>& text);
    
    int getNumber() const;
    Time getStartTime() const;
    Time getEndTime() const;
    const std::vector<std::string>& getText() const;
    
    bool isValid() const;
    
private:
    int number;
    Time startTime;
    Time endTime;
    std::vector<std::string> text;
};

