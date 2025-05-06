#include "SubtitleParser.h"
#include "SubtitleProcessor.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <srt_file>" << std::endl;
        return 1;
    }
    
    try {
        auto subtitles = SubtitleParser::parseFromFile(argv[1]);
        auto commands = SubtitleProcessor::processSubtitles(subtitles);
        
        for (const auto& cmd : commands) {
            std::cout << cmd << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}