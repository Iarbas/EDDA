cmake_minimum_required (VERSION 3.10.2)
project (EDDAmodel)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# As the project uses only odeint from Boost, the version 1.60.0 is sufficient
# (latest odeint version).
find_package(Boost 1.60.0 REQUIRED)

# Create a static library.
include_directories(include)

ADD_LIBRARY( ${PROJECT_NAME} STATIC src/simple_model.cpp )
target_link_libraries( ${PROJECT_NAME} stdc++fs )
add_dependencies( ${PROJECT_NAME} copy_headers_model )


# Copy the headers in the projects own file managment. 
add_custom_target( copy_headers_model )
add_dependencies( copy_headers_model create_folders )

add_custom_command(
        TARGET copy_headers_model PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy include/simple_model.hpp ${CMAKE_HEADERS_OUTPUT_DIRECTORY}/)

