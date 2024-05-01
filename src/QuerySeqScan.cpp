#include "../include/QuerySeqScan.hpp"
#include "../include/DataPoint.hpp"
#include "../include/DataBase.hpp"
#include "../include/Utils.hpp"
#include <iostream>

QuerySeqScan::QuerySeqScan(std::ifstream& ifs, const DataBase& db) : Query(ifs,db){
}

QuerySeqScan::~QuerySeqScan(){
}

void QuerySeqScan::run (int& switchquery){
     for (int i = 0; i< _db.GetSize(); ++i) {
          const DataPoint& p = _db.GetPoint(i);
          if (!IsValid(p)) continue;
          float dist = getDistance(p.GetData(), _data);
          
          _answer.CheckAndAdd(i,dist);
     } 
     _isFinished = 1;
}

