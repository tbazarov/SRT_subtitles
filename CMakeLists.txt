cmake_minimum_required(VERSION 3.10)
project(SRT_subtitles)

set(CMAKE_CXX_STANDARD 17)

# Main executable
add_executable(SRT_subtitles
    Time.cpp 
    Subtitle.cpp 
    SubtitleParser.cpp 
    SubtitleProcessor.cpp 
    main.cpp
)

# Test executable
add_executable(SRT_tests
    Time.cpp
    Subtitle.cpp
    SubtitleParser.cpp
    SubtitleProcessor.cpp
    SRT_tests.cpp
)

# Find GTest
find_package(GTest REQUIRED)
target_link_libraries(SRT_tests GTest::GTest GTest::Main)

enable_testing()
add_test(NAME SRT_tests COMMAND SRT_tests)