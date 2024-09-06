#!/bin/bash

# Define directories
BUILD_DIR="cpp/bin"

# Check if the build directory exists
if [ -d "$BUILD_DIR" ]; then
    echo "Removing build files from $BUILD_DIR..."
    rm -rf "$BUILD_DIR"/*
    echo "Build files removed."
else
    echo "Build directory $BUILD_DIR does not exist."
fi

echo "Cleanup complete."
