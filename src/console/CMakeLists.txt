# Set flags for qt5 forms
set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

# Set flag standards for qt5
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms )

# Find packages
find_package( OpenCV CONFIG REQUIRED )
find_package( Qt5 COMPONENTS Widgets Svg REQUIRED )
find_path( BOOST_ASIO_INCLUDE_DIRS "boost/asio.hpp" )

# Specify Include Directories
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Qt5Widgets_INCLUDES} )

# Additional Library Directories
link_directories( ${OpenCV_LIB_DIR} )

# Define source files to compile
file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_SOURCE_DIR}/libs/* ${CMAKE_CURRENT_SOURCE_DIR}/forms/* )

# Add executable
add_executable( console ${SRCFILES} )

# Link libraries
target_link_libraries( console PRIVATE Qt5::Widgets Qt5::Svg ${OpenCV_LIBS} )
target_include_directories( console PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${BOOST_ASIO_INCLUDE_DIRS} )

# Copy executable and assets to main build folder
COPY_FILE_INTO_DIRECTORY_IF_CHANGED( ${CMAKE_BINARY_DIR}/src/console/console ${CMAKE_BINARY_DIR} console )
COPY_DIRECTORY_IF_CHANGED( ${CMAKE_SOURCE_DIR}/assets ${CMAKE_SOURCE_DIR}/build/assets console )