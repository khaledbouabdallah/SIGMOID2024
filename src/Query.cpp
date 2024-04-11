#include "Query.hpp"

#include "globals.hpp"

#include <fstream>

#include "DataBase.hpp"

using namespace std;

Query::Query(ifstream& ifs, const DataBase& db): _db(db){
     _data = new float[DATA_SIZE];
     float dummyfloat;
     ifs.read((char *)&dummyfloat, sizeof(uint32_t));
     _type=int(dummyfloat);
     ifs.read((char *)&dummyfloat, sizeof(uint32_t));
     _c=int(dummyfloat);
     ifs.read((char *)&_tsl, sizeof(uint32_t));
     ifs.read((char *)&_tsr, sizeof(uint32_t));
     ifs.read((char *)_data, DATA_SIZE * sizeof(uint32_t));
     
     //switch(_type):
     //     case 0:
     //          _indices = _db.get
          
          
     //     _answer.InitWithIndices(_db.
}

void Query::run(int& s){
}

Query::~Query(){
     delete[] _data;
}
