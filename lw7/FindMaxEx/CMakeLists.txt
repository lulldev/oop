cmake_minimum_required(VERSION 3.6)
project(FindMaxEx)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(FindMaxEx ${SOURCE_FILES})

project(FindMaxExTesting)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES tests/Tests.cpp tests/Tests.h FindMaxEx/FindMaxEx.h tests/data/Athlete.cpp tests/data/Athlete.h)
add_executable(FindMaxTesting ${SOURCE_FILES})
target_link_libraries(FindMaxTesting gtest_main)