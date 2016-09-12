cmake_minimum_required(VERSION 3.6)
project(ramp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Source/main.cpp Source/Display.cpp Headers/constants.h)
add_executable(ramp ${SOURCE_FILES})