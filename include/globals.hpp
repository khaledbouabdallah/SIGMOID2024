#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

using std::string;

#define DATA_SIZE 100

extern int done;
// Add your constant declarations here

const int VECTOR_SIZE = 102; // The size of the vector
const int QUERY_SIZE = 104; // The size of the query type
; // The size of the data without the timestamp and c
const int K = 100; // The number of nearest neighbors to find
const string DATA_FILE = "../data/dummy-data.bin"; // The path to the data file
const string QUERY_FILE = "../data/dummy-query.bin"; // The path to the query file
const string OUTPUT_FILE = "../output.bin"; // The path to the output file

#endif // CONSTANTS_HPP
