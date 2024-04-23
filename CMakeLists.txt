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
set(SOURCES src/main.cpp src/DataBase.cpp src/DataPoint.cpp src/Query.cpp src/QuerySet.cpp src/Answer.cpp src/SAX.cpp src/Utils.cpp src/QueryRunManager.cpp src/QuerySeqScan.cpp src/QuerySeqScanRange.cpp src/QueryThreadData.cpp src/QuerySeqScanIncremental.cpp src/QuerySAXTrie.cpp src/QuerySeqScanRangeIncremental.cpp src/QueryQueue.cpp src/SortUtils.cpp src/QueryRangeSAXFilter.cpp)
#set(SOURCES tests/sax.cpp src/DataBase.cpp src/DataPoint.cpp src/Query.cpp src/QuerySet.cpp src/Answer.cpp src/SAX.cpp src/Utils.cpp src/QuerySeqScanRange.cpp)
# Add the executable
add_executable(TER ${SOURCES})
