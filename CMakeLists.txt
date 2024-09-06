cmake_minimum_required(VERSION 3.10)
project(SudokuApp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the build type
set(CMAKE_BUILD_TYPE Debug)

# Set compiler flags for debugging
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")

# Include directory
include_directories(cpp/include)

# Add source files
file(GLOB SOURCES "cpp/src/*.cpp")

# Define the executable
add_executable(my_program ${SOURCES})

# Specify the output directory for the executable
set_target_properties(my_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/cpp/bin")
