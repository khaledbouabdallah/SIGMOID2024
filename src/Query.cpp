#include "Query.hpp"

#include "globals.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include "DataBase.hpp"
#include "DataPoint.hpp"
#include <vector>

using namespace std;

Query::Query(ifstream& ifs, const DataBase& db): _db(db), _isFinished(0), _pointsToExamine(db.GetSize()){
     _data = new float[DATA_SIZE];
     float dummyfloat;
     ifs.read((char *)&dummyfloat, sizeof(uint32_t));
     _type=int(dummyfloat);
     ifs.read((char *)&dummyfloat, sizeof(uint32_t));
     _c=int(dummyfloat);
     ifs.read((char *)&_tsl, sizeof(uint32_t));
     ifs.read((char *)&_tsr, sizeof(uint32_t));
     ifs.read((char *)_data, DATA_SIZE * sizeof(uint32_t));   
     
     //normalize
     for (int  i =0; i>DATA_SIZE; ++i)
          _data[i] = (_data[i]-_db.GetGlobalMean()) / _db.GetGlobalStd();
}

void Query::InitIndicesAndRanges(){
         
     //fetch indice and range data
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
      _pointsToExamine = _endIndice-_startIndice+1;
}

void Query::InitAnswerWithRanges(){
      //feed Answer instance with initial data
      //it assumes correct ranges
      for (int i = 0; i<DATA_SIZE; ++i) {
          int crti = _startIndice+i;
          if (crti>_endIndice) 
               break;
          const DataPoint& dp = _db.GetPoint(_indices[crti]);
          float dist = getDistance(dp.GetData(), _data);
          _answer.CheckAndAdd(_indices[crti],dist); 
      }
}

void Query::WriteOutput(ofstream& ofs) {
     _answer.FillMissing();
     _answer.WriteOutput(ofs);
}

int Query::IsValid(const DataPoint& p) const {
     if ((_type == 1 || _type ==3) && (_c!=p.GetC())) return 0;
     if ((_type == 2 || _type ==3) && (_tsl>p.GetTS() || _tsr<p.GetTS())) return 0;
     return 1;
}

int Query::IsFinished() {
     return _isFinished;
}


void Query::SetSAX(uint64_t* sax){
     _sax = sax;
}

void Query::CheckIndices(const vector<int>&indices) {
     for (int ind:indices) {
           const DataPoint& p = _db.GetPoint(ind);
           if (!IsValid(p)) continue;
           float realDistance = getDistance(p.GetData(), _data);
          _answer.CheckAndAdd(ind,realDistance);
     }
}

Query::~Query(){
     delete[] _data;
}
