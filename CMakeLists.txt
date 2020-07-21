# the minimum version of CMake required
cmake_minimum_required( VERSION 3.8 )

#Set an environmental variable that locates file vcpkg.cmake found somewhere in vcpkg root
if( NOT DEFINED ENV{VCPKG} )
    message( STATUS "VCPKG environment variable is undefined" )
endif()
set( CMAKE_TOOLCHAIN_FILE $ENV{VCPKG} )

#Uncomment these when running on linux target
#file(GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.h)
#file(GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.h)

#Uncomment these when running on non-linux target
file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/camera.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/include/camera.h )
file( GLOB TESTFILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/camera.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/include/camera.h )

# Create Project
project( tractor )
add_executable( main ${SRCFILES} )
add_executable( tests ${TESTFILES} )

enable_testing()

# Find Package
find_package( OpenCV CONFIG REQUIRED )
find_package( GTest CONFIG REQUIRED )
find_package( jsoncpp CONFIG REQUIRED ) 

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${GTest_INCLUDE_DIRS} )

# Additional Library Directories
link_directories( ${OpenCV_LIB_DIR} )
link_directories( ${GTest_LIB_DIR} )

# Additional Dependencies
target_link_libraries( main ${OpenCV_LIBS} opencv_aruco jsoncpp_lib)
target_link_libraries( tests PRIVATE ${OpenCV_LIBS} opencv_aruco jsoncpp_lib GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main )

add_test( AllTestsInMain main )

target_include_directories( main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include )
target_include_directories( tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include )