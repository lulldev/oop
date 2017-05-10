cmake_minimum_required(VERSION 3.6)
project(BadWordsFilter)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp BadWordsFilter/BadWordsFilter.cpp BadWordsFilter/BadWordsFilter.h)
add_executable(BadWordsFilter ${SOURCE_FILES})

project(BadWordsFilter_testing)

set(SOURCE_FILES testing.cpp BadWordsFilter/BadWordsFilter.cpp BadWordsFilter/BadWordsFilter.h)
add_executable(BadWordsFilter_testing ${SOURCE_FILES})