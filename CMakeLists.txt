cmake_minimum_required(VERSION 3.6)
project(ramp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(test_ramper src/Display.cpp src/functions.cpp src/RGB565.cpp
        tests/RGB565_tests.h tests/RGB565_tests.cpp tests/functions_tests.h tests/functions_tests.cpp
        tests/tests.cpp)

set(HEADER_FILES headers/constants.h headers/Display.h headers/functions.h headers/RGB565.h)
set(SOURCE_FILES src/main.cpp src/Display.cpp src/functions.cpp src/RGB565.cpp)
add_executable(run_ramper ${HEADER_FILES} ${SOURCE_FILES})