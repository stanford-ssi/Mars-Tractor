#Uncomment these when running on linux target
file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_SOURCE_DIR}/libs/* )

#Uncomment these when running on non-linux target
#  file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_SOURCE_DIR}/libs/* )
#  list( REMOVE_ITEM SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/include/dualshock.h ${CMAKE_CURRENT_SOURCE_DIR}/libs/dualshock.cpp )

# Add executable
add_executable( target ${SRCFILES} )

# Find Package
find_package( OpenCV CONFIG REQUIRED )
find_package( jsoncpp CONFIG REQUIRED )
find_path( BOOST_SIGNALS2_INCLUDE_DIRS "boost/signals2.hpp" )

# Specify Include Directories
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${jsoncpp_INCLUDE_DIRS} )

# Additional Library Directories
link_directories( ${OpenCV_LIB_DIR} )
link_directories( ${jsoncpp_LIB_DIR} )

# Link Dependencies
target_link_libraries( target ${OpenCV_LIBS} opencv_aruco jsoncpp_lib )

# Link Local Header Files
target_include_directories( target PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include )

# Copy executable to main build folder
COPY_FILE_INTO_DIRECTORY_IF_CHANGED( ${CMAKE_BINARY_DIR}/src/target/target ${CMAKE_BINARY_DIR} target )