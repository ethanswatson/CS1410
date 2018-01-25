cmake_minimum_required(VERSION 3.6)
project(hw3_frequency_analysis)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Record.hpp TestCases.cpp TestCases.hpp)
add_executable(hw3_frequency_analysis ${SOURCE_FILES})