# Macro definitions
MACRO( COPY_FILE_IF_CHANGED in_file out_file target )
    if( EXISTS ${in_file} )
    
        if( ${in_file} IS_NEWER_THAN ${out_file} )    
            message( STATUS "Copying file: ${in_file} to: ${out_file}" )
            ADD_CUSTOM_COMMAND (
                TARGET     ${target}
                POST_BUILD
                COMMAND    ${CMAKE_COMMAND}
                ARGS       -E copy ${in_file} ${out_file}
            )
        endif( ${in_file} IS_NEWER_THAN ${out_file} )
    endif ( EXISTS ${in_file} )
ENDMACRO( COPY_FILE_IF_CHANGED )

MACRO( COPY_FILE_INTO_DIRECTORY_IF_CHANGED in_file out_dir target )
    GET_FILENAME_COMPONENT( file_name ${in_file} NAME )
    COPY_FILE_IF_CHANGED( ${in_file} ${out_dir}/${file_name} ${target} )	
ENDMACRO(COPY_FILE_INTO_DIRECTORY_IF_CHANGED)

#Copy all files and directories in in_dir to out_dir. 
# Subtrees remain intact.
MACRO( COPY_DIRECTORY_IF_CHANGED in_dir out_dir target )
    message( STATUS "Copying directory ${in_dir}" )
    file( GLOB_RECURSE in_file_list ${in_dir}/* ${in_dir}/**/* )
    FOREACH( in_file ${in_file_list} )
            STRING( REGEX REPLACE ${in_dir} ${out_dir} out_file ${in_file} )
            COPY_FILE_IF_CHANGED( ${in_file} ${out_file} ${target} )
    ENDFOREACH( in_file )	
ENDMACRO( COPY_DIRECTORY_IF_CHANGED )

# the minimum version of CMake required
cmake_minimum_required( VERSION 3.8 )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

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
option( BUILD_DOC "Build documentation" ON )

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

