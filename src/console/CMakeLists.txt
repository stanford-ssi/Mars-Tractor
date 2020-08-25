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
find_package( Qt5 COMPONENTS Widgets REQUIRED )
find_path( BOOST_ASIO_INCLUDE_DIRS "boost/asio.hpp" )

# Define source files to compile
file( GLOB SRCFILES ${CMAKE_CURRENT_SOURCE_DIR}/cont.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_SOURCE_DIR}/libs/* )

# Add executable
add_executable( console ${SRCFILES} )

# Link libraries
target_link_libraries( console PRIVATE Qt5::Widgets )
target_include_directories( console PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include )