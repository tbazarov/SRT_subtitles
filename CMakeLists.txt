cmake_minimum_required(VERSION 3.14)
project(SubtitleTool)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build tests" OFF)

add_executable(runApp
    main.cpp
    Time.cpp
    Subtitle.cpp
    SubtitleParser.cpp
    SubtitleProcessor.cpp
)

if(BUILD_TESTS)
    find_package(GTest REQUIRED)
    add_executable(runUnitTests
        test_main.cpp
        TimeTest.cpp
        SubtitleTest.cpp
        SubtitleParserTest.cpp
        SubtitleProcessorTest.cpp
        Time.cpp
        Subtitle.cpp
        SubtitleParser.cpp
        SubtitleProcessor.cpp
    )
    target_link_libraries(runUnitTests GTest::GTest GTest::Main)
endif()