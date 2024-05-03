cmake_minimum_required(VERSION 3.10)
project(TER)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}") 
# This will place the executable in a "bin" directory at the project's root.


# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the build type
set(CMAKE_BUILD_TYPE Debug)

# Set the include directories
include_directories(include)


# Set the source files
set(SOURCES src/main.cpp src/QuerySAXLookaround.cpp   src/Kmeans.cpp src/QueryIVF.cpp src/IndexSAXTrie.cpp src/DataBase.cpp src/DataPoint.cpp src/Query.cpp src/QuerySet.cpp src/Answer.cpp src/SAX.cpp src/Utils.cpp src/QueryRunManager.cpp src/QuerySeqScan.cpp src/QuerySeqScanRange.cpp src/QueryThreadData.cpp src/QuerySeqScanIncremental.cpp src/QuerySeqScanRangeIncremental.cpp src/QueryQueue.cpp src/SortUtils.cpp src/QueryRangeSAXFilter.cpp src/QueryRangeSAXOnly.cpp)
#set(SOURCES tests/sax.cpp src/DataBase.cpp src/DataPoint.cpp src/Query.cpp src/QuerySet.cpp src/Answer.cpp src/SAX.cpp src/Utils.cpp src/QuerySeqScanRange.cpp)
# Add the executable
add_executable(TER ${SOURCES})


# Apply compiler flags
target_compile_options(TER PRIVATE 
    -march=native  
    -ffast-math 
    -O3 
)  
    
