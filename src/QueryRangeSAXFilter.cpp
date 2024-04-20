#include "QueryRangeSAXFilter.hpp"
#include "Utils.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"
#include <iostream>

using namespace std;

QueryRangeSAXFilter::QueryRangeSAXFilter(std::ifstream& ifs, const DataBase& db) : Query(ifs,db){
     InitIndicesAndRanges();
     InitAnswerWithRanges();
}

QueryRangeSAXFilter::~QueryRangeSAXFilter(){
}

void QueryRangeSAXFilter::run (int& switchquery){
     for (int i = _startIndice+DATA_SIZE; i< _endIndice; ++i) {
          const DataPoint& p = _db.GetPoint(_indices[i]);
           if (GetSAXDistance(p) > getDistance(_data, p.GetData()))
               cout<<"BIG ERROR SAX"<<endl;
          if (GetSAXDistance(p)>_answer._distMax)
               continue; //filter
          //cout<<i<<endl;
          float dist = getDistance(p.GetData(), _data);
          _answer.CheckAndAdd(_indices[i],dist);
     } 
     _isFinished = 1;
}
