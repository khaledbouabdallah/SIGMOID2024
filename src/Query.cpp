#include "Query.hpp"

#include "globals.hpp"

#include <fstream>

using namespace std;

Query::Query(ifstream& ifs){
     _data = new float[DATA_SIZE];
     ifs.read((char *)&_type, sizeof(uint32_t));
     ifs.read((char *)&_c, sizeof(uint32_t));
     ifs.read((char *)&_tsl, sizeof(uint32_t));
     ifs.read((char *)&_tsr, sizeof(uint32_t));
     ifs.read((char *)_data, DATA_SIZE * sizeof(uint32_t));
}

void Query::run(int& s){
}

Query::~Query(){
     delete[] _data;
}
