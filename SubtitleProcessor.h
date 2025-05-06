#pragma once

#include "Subtitle.h"
#include <vector>
#include <string>

class SubtitleProcessor {
public:
    static std::vector<std::string> processSubtitles(const std::vector<Subtitle>& subtitles);
    
private:
    struct Event {
        Time time;
        bool isStart;
        const Subtitle* subtitle;
        
        bool operator<(const Event& other) const {
            if (time == other.time) {
                return isStart && !other.isStart;
            }
            return time < other.time;
        }
    };
};
