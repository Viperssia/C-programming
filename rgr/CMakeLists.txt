cmake_minimum_required(VERSION 3.12)
project(TextFrequencyAnalyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOGIC_SOURCES src/analyzer.cpp src/analyzer.hpp)

add_executable(analyzer_app src/main.cpp ${LOGIC_SOURCES})

add_executable(unit_tests tests/test_main.cpp ${LOGIC_SOURCES})
