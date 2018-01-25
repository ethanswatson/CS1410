cmake_minimum_required(VERSION 3.6)
project(hw4_big_integer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BigInteger.cpp BigInteger.hpp TestCases.cpp TestCases.hpp)
add_executable(hw4_big_integer ${SOURCE_FILES})