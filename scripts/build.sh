#!/bin/bash

# Define the build directory
BUILD_DIR="build"

# Create the build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir "$BUILD_DIR"
else
    echo "Build directory already exists."
fi

# Navigate to the build directory
cd "$BUILD_DIR" || { echo "Failed to enter build directory."; exit 1; }

# Run CMake to configure the project
echo "Running CMake..."
cmake .. || { echo "CMake configuration failed."; exit 1; }

# Build the project
echo "Building the project..."
make || { echo "Build failed."; exit 1; }

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful!"
else
    echo "Build failed."
    exit 1
fi
