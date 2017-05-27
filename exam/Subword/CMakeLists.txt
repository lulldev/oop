cmake_minimum_required(VERSION 3.6)
project(subword)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(subword ${SOURCE_FILES})