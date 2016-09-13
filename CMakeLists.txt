cmake_minimum_required(VERSION 3.6)
project(ramp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(test)

set(HEADER_FILES headers/constants.h headers/Display.h headers/functions.h headers/RGB565.h)
set(SOURCE_FILES src/main.cpp src/Display.cpp src/functions.cpp src/RGB565.cpp)
add_executable(run_ramper ${HEADER_FILES} ${SOURCE_FILES})