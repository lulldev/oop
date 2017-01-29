cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

###########################################################################################

project(oop_lw4)
set(SOURCE_FILES main.cpp VolumeBodies/CBody.cpp VolumeBodies/CBody.h tests/Tests.h VolumeBodies/CSphere.cpp VolumeBodies/CSphere.h VolumeBodies/FigureTypes.h VolumeBodies/CCone.cpp VolumeBodies/CCone.h VolumeBodies/CParallelepiped.cpp VolumeBodies/CParallelepiped.h VolumeBodies/CCylinder.cpp VolumeBodies/CCylinder.h ConsoleProgram/ConsoleProgram.cpp ConsoleProgram/ConsoleProgram.h VolumeBodies/CCompound.cpp VolumeBodies/CCompound.h VolumeBodies/VolumeBodies.h VolumeBodies/Helpers.h VolumeBodies/Helpers.cpp)
add_executable(oop_lw4 ${SOURCE_FILES})
target_link_libraries(oop_lw4)

###########################################################################################

project(oop_lw4_testing)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES tests/Tests.cpp tests/Tests.h VolumeBodies/CBody.cpp VolumeBodies/CBody.h tests/Tests.h VolumeBodies/CSphere.cpp VolumeBodies/CSphere.h VolumeBodies/FigureTypes.h VolumeBodies/CCone.cpp VolumeBodies/CCone.h VolumeBodies/CParallelepiped.cpp VolumeBodies/CParallelepiped.h VolumeBodies/CCylinder.cpp VolumeBodies/CCylinder.h ConsoleProgram/ConsoleProgram.cpp ConsoleProgram/ConsoleProgram.h VolumeBodies/CCompound.cpp VolumeBodies/CCompound.h VolumeBodies/VolumeBodies.h VolumeBodies/Helpers.h VolumeBodies/Helpers.cpp)
add_executable(oop_lw4_testing ${SOURCE_FILES} tests/Tests.cpp tests/Tests.h VolumeBodies/CBody.cpp VolumeBodies/CBody.h tests/Tests.h)
target_link_libraries(oop_lw4_testing gtest gtest_main)