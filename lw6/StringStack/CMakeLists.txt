cmake_minimum_required(VERSION 3.6)
project(StringStack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(StringStack ${SOURCE_FILES})

###########################################################################################

project(TestStringStack)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES tests/Tests.cpp tests/Tests.h StringStack/StringStack.cpp StringStack/StringStack.h)
add_executable(TestStringStack ${SOURCE_FILES} tests/Tests.cpp tests/Tests.h)
target_link_libraries(TestStringStack gtest gtest_main)