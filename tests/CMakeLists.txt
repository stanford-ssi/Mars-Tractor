#Uncomment these when running on linux target
# file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/* ${CMAKE_CURRENT_SOURCE_DIR}/../src/target/**/* )

#Uncomment these when running on non-linux target
file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/* ${CMAKE_CURRENT_SOURCE_DIR}/../src/target/**/* )
list( REMOVE_ITEM SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/target/include/dualshock.h ${CMAKE_CURRENT_SOURCE_DIR}/../src/target/libs/dualshock.cpp )

# Add executable
add_executable( tests ${SRCFILES} )

# Find Package
find_package( OpenCV CONFIG REQUIRED )
find_package( GTest CONFIG REQUIRED )
find_package( jsoncpp CONFIG REQUIRED )
find_path( BOOST_SIGNALS2_INCLUDE_DIRS "boost/signals2.hpp" )

# Specify Include Directories
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${GTest_INCLUDE_DIRS} )
include_directories( ${jsoncpp_INCLUDE_DIRS} )

# Additional Library Directories
link_directories( ${OpenCV_LIB_DIR} )
link_directories( ${GTest_LIB_DIR} )
link_directories( ${jsoncpp_LIB_DIR} )
find_path(BOOST_SIGNALS2_INCLUDE_DIRS "boost/signals2.hpp")

# Link Dependencies
target_link_libraries( tests PRIVATE ${OpenCV_LIBS} opencv_aruco jsoncpp_lib GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main )
target_include_directories( tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src/target/include )