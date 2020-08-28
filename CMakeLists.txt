# the minimum version of CMake required
cmake_minimum_required( VERSION 3.8 )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Set Unix flags
if ( UNIX )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )
endif ()

# Create project
project( tractor )

# Add project subdirectories
add_subdirectory( src/console )
add_subdirectory( src/target )
add_subdirectory( tests )

# Generate Documentation
option( BUILD_DOC "Build documentation" OFF )

if ( BUILD_DOC )
find_package( Doxygen )
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