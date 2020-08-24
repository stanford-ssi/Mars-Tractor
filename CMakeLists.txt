# the minimum version of CMake required
cmake_minimum_required( VERSION 3.8 )

# Checks for VCPKG ENV
if( NOT DEFINED ENV{VCPKG} )
    message( STATUS "VCPKG environmental variable has not been set" )
endif()
set( CMAKE_TOOLCHAIN_FILE $ENV{VCPKG} )
list( APPEND CMAKE_MODULE_PATH ${VCPKG_ROOT_DIR}/downloads/tools )

#Uncomment these when running on linux target
#file(GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.h)
#file(GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/include/*.h)

#Uncomment these when running on non-linux target
file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**/* ${CMAKE_CURRENT_SOURCE_DIR}/src/*)
list( REMOVE_ITEM SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/dualshock.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/include/dualshock.h )
file( GLOB TESTFILES ${SRCFILES} ${CMAKE_CURRENT_SOURCE_DIR}/tests/* )
list( REMOVE_ITEM TESTFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Create Project
project( tractor )
add_executable( main ${SRCFILES} )
add_executable( tests ${TESTFILES} )

enable_testing()

# Find Package
find_package( OpenCV CONFIG REQUIRED )
find_package( GTest CONFIG REQUIRED )
find_package( jsoncpp CONFIG REQUIRED )
find_package( Doxygen )

# Specify Include Directories
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${GTest_INCLUDE_DIRS} )
include_directories( ${jsoncpp_INCLUDE_DIRS} )
find_path(BOOST_ASIO_INCLUDE_DIRS "boost/asio.hpp")
find_path(BOOST_SIGNALS2_INCLUDE_DIRS "boost/signals2.hpp")

# Additional Library Directories
link_directories( ${OpenCV_LIB_DIR} )
link_directories( ${GTest_LIB_DIR} )
link_directories( ${jsoncpp_LIB_DIR} )

# Link Dependencies
target_link_libraries( main ${OpenCV_LIBS} opencv_aruco jsoncpp_lib)
target_link_libraries( tests PRIVATE ${OpenCV_LIBS} opencv_aruco jsoncpp_lib GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main )

# Link Local Header Files
target_include_directories( main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include ${BOOST_ASIO_INCLUDE_DIRS} ${BOOST_SIGNALS2_INCLUDE_DIRS} )
target_include_directories( tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include ${BOOST_ASIO_INCLUDE_DIRS} ${BOOST_SIGNALS2_INCLUDE_DIRS} )

# Generate Documentation
option( BUILD_DOC "Build documentation" OFF )

if ( BUILD_DOC )
    if ( NOT DOXYGEN_FOUND )
    endif()

    # Set Input and Output Files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)

    # Request to Configure the File
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Build the Docs Together with the Application
    add_custom_target( doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
            
endif ()