cmake_minimum_required(VERSION 3.6)
project(MyStack)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(MyStack ${SOURCE_FILES})

###########################################################################################

project(TestMyStack)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES tests/Tests.cpp tests/Tests.h MyStack/MyStack.h)
add_executable(TestMyStack ${SOURCE_FILES})
target_link_libraries(TestMyStack gtest gtest_main)