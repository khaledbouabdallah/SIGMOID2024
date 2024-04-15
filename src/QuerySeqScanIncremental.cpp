#include "QuerySeqScanIncremental.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"
#include "Utils.hpp"
#include <iostream>

QuerySeqScanIncremental::QuerySeqScanIncremental(std::ifstream& ifs, const DataBase& db) : Query(ifs,db), _nextPointIndice(0){
}

QuerySeqScanIncremental::~QuerySeqScanIncremental(){
}

void QuerySeqScanIncremental::run (int& switchquery){
     switchquery = 0; //my turn now, don't stop me ! : p
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
          if (switchquery)
               break;
     } 
}

