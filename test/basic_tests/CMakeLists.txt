include_directories(${gtest_SOUCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runInputTests RGB565_tests.cpp function_tests.cpp
        ../../src/functions.cpp ../../src/RGB565.cpp ../../src/Display.cpp)

target_link_libraries(runInputTests gtest gtest_main)
