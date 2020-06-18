# the minimum version of CMake required
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXXFLAGES "${CMAKE_CXX_FLAGES} -std = c++14")

#project
project(tractor)

#testing
enable_testing()

#set(SOURCES src/"*.cpp" src/include/*.h)
file(GLOB SRCFILES src/main.cpp src/libs/*.cpp src/include*.h)
file(GLOB TESTFILES tests/tests.cpp src/libs/*.cpp src/include*.h)

#packages
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tractor ${SRCFILES})
add_executable(tests ${TESTFILES})

target_link_libraries( tractor Threads::Threads)
target_link_libraries( tractor ${OpenCV_LIBS})
target_link_libraries( tests ${GTEST_LIBRARIES} pthread)
target_include_directories(tractor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
