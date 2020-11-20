cmake_minimum_required (VERSION 3.11)
project (EDDA)

# Get the absolute path to the parent directory.
get_filename_component(PARENT_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)

message(STATUS "Installation path of the binaries, libs and headers: " ${PARENT_DIR})

# Define the locations all necessary files.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PARENT_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PARENT_DIR}/build/lib)
set(CMAKE_HEADERS_OUTPUT_DIRECTORY ${PARENT_DIR}/build/lib/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PARENT_DIR}/build/bin)

# C++ options.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_REQUIRED_FLAGS -std=c++17 -lstdc++fs)

# The version number.
set (EDDA_VERSION_MAJOR 0)
set (EDDA_VERSION_MINOR 1)

# Standard directory for the config files.
set (CONFIG_DIRECTORY ${PARENT_DIR}/build/configs)

# Standard directory for the test circuit files.
set (TEST_CIRCUIT_DIRECTORY ${PARENT_DIR}/build/test_circuits)

# Create the additional folders to organize the configs, images etc. in a better way.
add_custom_target(create_folders)

add_custom_command(
        TARGET create_folders PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_HEADERS_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CONFIG_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${TEST_CIRCUIT_DIRECTORY})

# Add subfolders of the project.
add_subdirectory(EDDAmisc/Config_Reader)
# add_subdirectory(EDDAcontrol)
# add_subdirectory(EDDAestimate)
add_subdirectory(EDDAmodel)
# add_subdirectory(EDDAoptimal)
# add_subdirectory(EDDApath)
add_subdirectory(EDDAsim)
# add_subdirectory(EDDAvalidate)

