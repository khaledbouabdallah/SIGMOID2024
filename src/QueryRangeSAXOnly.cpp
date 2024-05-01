#include "../include/QueryRangeSAXOnly.hpp"
#include "../include/Utils.hpp"
#include "../include/DataPoint.hpp"
#include "../include/DataBase.hpp"
#include <iostream>

using namespace std;

QueryRangeSAXOnly::QueryRangeSAXOnly(std::ifstream& ifs, const DataBase& db) : Query(ifs,db){
     InitIndicesAndRanges();

}

QueryRangeSAXOnly::~QueryRangeSAXOnly(){
}

void QueryRangeSAXOnly::run (int& switchquery){
      //feed Answer instance with initial data
      //by using sax distances

      for (int i = 0; i<DATA_SIZE; ++i) {
          int crti = _startIndice+i;
          if (crti>_endIndice) 
               break;
          const DataPoint& dp = _db.GetPoint(_indices[crti]);
          float saxDistance = _db.GetSAXDistance(dp.Getsax(), _sax); 
          _answer.CheckAndAdd(_indices[crti],saxDistance); 
      }
     for (int i = _startIndice+DATA_SIZE; i< _endIndice; ++i) {
          const DataPoint& p = _db.GetPoint(_indices[i]);

          float saxDistance = _db.GetSAXDistance(p.Getsax(), _sax); 
          
          _answer.CheckAndAdd(_indices[i],saxDistance);
     } 

     _isFinished = 1;
}

          
        
