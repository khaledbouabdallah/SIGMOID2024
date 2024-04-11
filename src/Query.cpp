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
     
     switch(_type)
     {
          case 0:
               _indices = _db.GetNormalIndices();
               _startIndice = 0;
               _endIndice = _db.GetSize();
               break;
          case 1:
               _indices = _db.GetIndicesSortedByCatAndTS();
               _db.GetCatRange(_c, _startIndice, _endIndice);
               break;
          case 2:
               _indices = _db.GetIndicesSortedByTS();
               _db.GetTSRange(_tsl, _tsr, _startIndice, _endIndice);
               break;
          case 3:
               _indices = _db.GetIndicesSortedByCatAndTS();
               _db.GetCatAndTSRange(_c, _tsl, _tsr, _startIndice, _endIndice);
               break; 
      }

}

void Query::run(int& s){
}

Query::~Query(){
     delete[] _data;
}
