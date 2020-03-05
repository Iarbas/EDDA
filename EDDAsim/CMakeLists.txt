cmake_minimum_required (VERSION 3.10.2)
project (EDDAsim)

# This command and the FindSFML.cmake file in cmake_modules is needed to find SFML.
# message(STATUS "CMAKE_MODULE_PATH: " ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Find needed packages.
find_package(OpenGL)
find_package(SFML 2 REQUIRED COMPONENTS graphics window system )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  config_for_cmake/cmake_config.h.in
  include/cmake_config.h
  )
 
# add the binary tree to the search path for include files
# so that we will find config.h
include_directories(include 
                    ${CMAKE_HEADERS_OUTPUT_DIRECTORY})

add_executable(${PROJECT_NAME} src/main.cpp src/visual2d.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(${PROJECT_NAME}
    ${SFML_LIBRARIES} 
    ${SFML_DEPENDENCIES}
    ${LIBYAML_LIBRARY}
    Config_Reader    
    )

add_dependencies( ${PROJECT_NAME} copy_config copy_circuits Config_Reader)

# Copy the config file and circuit files in the projects own file managment. 
add_custom_target(copy_config)
add_dependencies( copy_config create_folders )

add_custom_command(
        TARGET copy_config PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_LIST_DIR}/config/sim.config ${CONFIG_DIRECTORY}/sim.config)

add_custom_target(copy_circuits)
add_dependencies( copy_circuits create_folders )

add_custom_command(
        TARGET copy_circuits PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_LIST_DIR}/circuits/Circle ${TEST_CIRCUIT_DIRECTORY}/Circle)

