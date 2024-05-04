#include "../include/QuerySeqScanIncremental.hpp"
#include "../include/DataPoint.hpp"
#include "../include/DataBase.hpp"
#include "../include/Utils.hpp"
#include <iostream>

QuerySeqScanIncremental::QuerySeqScanIncremental(std::ifstream& ifs, const DataBase& db) : Query(ifs,db), _nextPointIndice(0){
}

QuerySeqScanIncremental::~QuerySeqScanIncremental(){
}

void QuerySeqScanIncremental::run (int& switchquery){
     while(1) {
          if (_nextPointIndice>=_db.GetSize()) {
               _isFinished = 1;
               break;
          }
          //examine one point
          const DataPoint& p = _db.GetPoint(_nextPointIndice);
          if (IsValid(p)) {
               float dist = getDistance(p.GetData(), _data);
               _answer.CheckAndAdd(_nextPointIndice,dist);
          }
          //save next point indice
          _nextPointIndice++;
          //check that I can run some more
          if (switchquery || done)
               break;
     } 
}

void QuerySeqScanIncremental::PrintDelta(){
     cout<<"remaining "<<_db.GetSize()-_nextPointIndice<<endl;
}

