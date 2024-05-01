#include "../include/QuerySeqScanRange.hpp"
#include "../include/Utils.hpp"
#include "../include/DataPoint.hpp"
#include "../include/DataBase.hpp"
#include <iostream>

using namespace std;

QuerySeqScanRange::QuerySeqScanRange(std::ifstream& ifs, const DataBase& db) : Query(ifs,db){
     InitIndicesAndRanges();
     InitAnswerWithRanges();
}

QuerySeqScanRange::~QuerySeqScanRange(){
}

void QuerySeqScanRange::run (int& switchquery){
     for (int i = _startIndice+DATA_SIZE; i< _endIndice; ++i) {
          const DataPoint& p = _db.GetPoint(_indices[i]);
          float dist = getDistance(p.GetData(), _data);
          _answer.CheckAndAdd(_indices[i],dist);
     } 
     _isFinished = 1;
}
