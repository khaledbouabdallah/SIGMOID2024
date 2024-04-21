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
          /*
          if (GetSAXDistance(p) > getDistance(_data, p.GetData())) {
               cout<<"BIG ERROR SAX"<<endl;
               for (int j = 0; j< 10; ++j)
                    cout<<p.Getsax()[j]<<" ";
               
               cout<<endl;
               for (int j = 0; j< 10; ++j)
                    cout<<_sax[j]<<" ";   
               cout<<GetSAXDistance(p)<<endl;
               cout<<getDistance(_data, p.GetData())<<endl;  
               exit(1);
           }
           */
          if (GetSAXDistance(p)>_answer._distMax)
               continue; //filter
          float dist = getDistance(p.GetData(), _data);
          _answer.CheckAndAdd(_indices[i],dist);
     } 
     _isFinished = 1;
}
