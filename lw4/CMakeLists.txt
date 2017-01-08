cmake_minimum_required(VERSION 3.6)
project(oop_lw4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES tests/Tests.cpp tests/Tests.h VolumeBodies/CBody.cpp VolumeBodies/CBody.h tests/Tests.h)
add_executable(oop_lw4 ${SOURCE_FILES} tests/Tests.cpp tests/Tests.h VolumeBodies/CBody.cpp VolumeBodies/CBody.h tests/Tests.h)
target_link_libraries(oop_lw4 gtest gtest_main)