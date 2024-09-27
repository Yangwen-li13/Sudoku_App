BUILD_DIR="build"
BIN_DIR="cpp/bin"

remove_dir_if_exists() {
    local dir=$1
    if [ -d "$dir" ]; then
        echo "Removing directory $dir..."
        rm -rf "$dir"
        echo "Directory $dir removed."
    else
        echo "Directory $dir does not exist."
    fi
}

remove_dir_if_exists "$BUILD_DIR"

remove_dir_if_exists "$BIN_DIR"

echo "Cleanup complete."
