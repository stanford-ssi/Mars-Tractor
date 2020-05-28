# the minimum version of CMake required
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXXFLAGES "${CMAKE_CXX_FLAGES} -std = c++14")
#project
project(tractor)


#set(SOURCES src/"*.cpp" src/include/*.h)
file(GLOB SRCFILES src/main.cpp src/libs/*.cpp src/include*.h)
file(GLOB TESTFILES tests/dsTest.cpp src/libs/*.cpp src/include*.h)

#packages
find_package(OpenCV REQUIRED)

add_executable(tractor ${SRCFILES})
add_executable(tests ${TESTFILES})

target_link_libraries( tractor ${OpenCV_LIBS})
target_include_directories(tractor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
#target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

# required for testing
#include(CTest)

# required modules for task
#include(CheckIncludeFile)
#include(CheckIncludeFileCXX)
#include(CheckIncludeFiles)
#include(ExternalProject)
# TO BE CREATED
#include(libs/opencv.cmake)

# add the files in the include directory to be included
# compile all the source code

# sub-directories that CMake scans
#add_subdirectory(include)
#add_subdirectory(libs)
#add_subdirectory(src)
#add_subdirectory(test)