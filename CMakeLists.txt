# the minimum version of CMake required
cmake_minimum_required( VERSION 3.8 )

# Checks for VCPKG ENV
if( NOT DEFINED ENV{VCPKG} )
    message( STATUS "VCPKG environmental variable has not been set" )
endif()
set( CMAKE_TOOLCHAIN_FILE $ENV{VCPKG} )
list( APPEND CMAKE_MODULE_PATH ${VCPKG_ROOT_DIR}/downloads/tools )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Create project
project( tractor )

# Add project subdirectories
add_subdirectory( src/console )
add_subdirectory( src/target )
add_subdirectory( tests )
enable_testing()


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