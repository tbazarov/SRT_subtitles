#include "SubtitleProcessor.h"
#include <algorithm>
#include <sstream>

std::vector<std::string> SubtitleProcessor::processSubtitles(const std::vector<Subtitle>& subtitles) {
    std::vector<Event> events;
    std::vector<std::string> commands;
    std::vector<const Subtitle*> activeSubtitles;
    
    // Create events
    for (const auto& subtitle : subtitles) {
        events.push_back({subtitle.getStartTime(), true, &subtitle});
        events.push_back({subtitle.getEndTime(), false, &subtitle});
    }
    
    // Sort events
    std::sort(events.begin(), events.end());
    
    // Process events
    for (const auto& event : events) {
        if (event.isStart) {
            // SHOW TEXT command
            activeSubtitles.push_back(event.subtitle);
            std::ostringstream oss;
            oss << event.time << " SHOW TEXT \"";
            for (size_t i = 0; i < activeSubtitles.size(); ++i) {
                const auto& textLines = activeSubtitles[i]->getText();
                for (size_t j = 0; j < textLines.size(); ++j) {
                    if (i != 0 || j != 0) oss << " ";
                    oss << textLines[j];
                }
            }
            oss << "\"";
            commands.push_back(oss.str());
        } else {
            // HIDE TEXT command
            auto it = std::find(activeSubtitles.begin(), activeSubtitles.end(), event.subtitle);
            if (it != activeSubtitles.end()) {
                activeSubtitles.erase(it);
                std::ostringstream oss;
                oss << event.time << " HIDE TEXT";
                commands.push_back(oss.str());
                
                // If there are still active subtitles, show them again
                if (!activeSubtitles.empty()) {
                    oss.str("");
                    oss << event.time << " SHOW TEXT \"";
                    for (size_t i = 0; i < activeSubtitles.size(); ++i) {
                        const auto& textLines = activeSubtitles[i]->getText();
                        for (size_t j = 0; j < textLines.size(); ++j) {
                            if (i != 0 || j != 0) oss << " ";
                            oss << textLines[j];
                        }
                    }
                    oss << "\"";
                    commands.push_back(oss.str());
                }
            }
        }
    }
    
    return commands;
}