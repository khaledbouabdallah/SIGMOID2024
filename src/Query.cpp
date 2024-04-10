#include "Query.hpp"

#include "globals.hpp"

#include <fstream>

using namespace std;

Query::Query(ifstream& ifs){
     _data = new float[DATA_SIZE];
     ifs.read((char *)&_c, sizeof(int));
     ifs.read((char *)&_tsl, sizeof(float));
     ifs.read((char *)&_tsr, sizeof(float));
     ifs.read((char *)_data, DATA_SIZE * sizeof(float));
}

Query::~Query(){
     delete[] _data;
}
