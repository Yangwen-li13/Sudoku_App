BUILD_DIR="build"

if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir "$BUILD_DIR"
else
    echo "Build directory already exists."
fi
cd "$BUILD_DIR" || { echo "Failed to enter build directory."; exit 1; }

echo "Running CMake..."
cmake .. || { echo "CMake configuration failed."; exit 1; }

echo "Building the project..."
make || { echo "Build failed."; exit 1; }

if [ $? -eq 0 ]; then
    echo "Build successful!"
else
    echo "Build failed."
    exit 1
fi
