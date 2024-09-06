# Define the directory for binaries and include
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/cpp/bin)
include_directories(${CMAKE_SOURCE_DIR}/cpp/include)

# Find source files
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(my_program ${SOURCES})

# Ensure the executable is placed in the specified directory
set_target_properties(my_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/cpp/bin)
