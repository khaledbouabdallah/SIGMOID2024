#include "Query.hpp"

#include "globals.hpp"

#include <fstream>

#include "DataBase.hpp"

using namespace std;

Query::Query(ifstream& ifs, const DataBase& db): _db(db){
     _data = new float[DATA_SIZE];
     ifs.read((char *)&_type, sizeof(uint32_t));
     ifs.read((char *)&_c, sizeof(uint32_t));
     ifs.read((char *)&_tsl, sizeof(uint32_t));
     ifs.read((char *)&_tsr, sizeof(uint32_t));
     ifs.read((char *)_data, DATA_SIZE * sizeof(uint32_t));
     
     //if (_type == 1)
     //     _answer.InitWithIndices(_db.
}

void Query::run(int& s){
}

Query::~Query(){
     delete[] _data;
}
