#include "QuerySeqScanRange.hpp"
#include "Utils.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"
#include <iostream>

using namespace std;

QuerySeqScanRange::QuerySeqScanRange(std::ifstream& ifs, const DataBase& db) : Query(ifs,db){
     InitIndicesAndRanges();
     InitAnswerWithRanges();
}

QuerySeqScanRange::~QuerySeqScanRange(){
}

void QuerySeqScanRange::run (int& switchquery){
     //cout<<_startIndice<<" "<<_endIndice<<endl;
     for (int i = _startIndice+DATA_SIZE; i< _endIndice; ++i) {
          //cout<<i<<" "<<_indices[i]<<endl;
          const DataPoint& p = _db.GetPoint(_indices[i]);
          float dist = distance(p.GetData(), _data);
          _answer.CheckAndAdd(_indices[i],dist);
     } 
}
