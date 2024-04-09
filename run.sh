#!/bin/bash

# Define variables
BUILD_DIR="build"
EXECUTABLE="TER"

# Create build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Navigate to build directory
cd $BUILD_DIR

# Run CMake to generate build files
cmake ..

# Build the project
make

# Check if the build was successful
if [ $? -eq 0 ]; then
    # Run the executable
    ./"$EXECUTABLE"
else
    echo "Build failed. Exiting."
fi
