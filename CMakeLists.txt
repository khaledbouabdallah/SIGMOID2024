cmake_minimum_required(VERSION 3.10)
project(TER)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the build type
set(CMAKE_BUILD_TYPE Debug)

# Set the include directories
include_directories(include)


# Set the source files
set(SOURCES src/main.cpp src/DataBase.cpp src/DataPoint.cpp src/Query.cpp src/QuerySet.cpp src/Utils.cpp)

# Add the executable
add_executable(TER ${SOURCES})
