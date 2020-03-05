cmake_minimum_required (VERSION 3.10.2)
project (Config_Reader)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Create a static library.
include_directories(include)

ADD_LIBRARY( ${PROJECT_NAME} STATIC src/readConfig.cpp )
target_link_libraries( ${PROJECT_NAME} stdc++fs )
add_dependencies( ${PROJECT_NAME} copy_headers_reader )

# Copy the headers in the projects own file managment. 
add_custom_target( copy_headers_reader )
add_dependencies( copy_headers_reader create_folders )

add_custom_command(
        TARGET copy_headers_reader PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy include/readConfig.hpp ${CMAKE_HEADERS_OUTPUT_DIRECTORY}/)

