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
     int countfiltered = 0;
     for (int i = _startIndice+DATA_SIZE; i< _endIndice; ++i) {
          const DataPoint& p = _db.GetPoint(_indices[i]);
          cout<<GetSAXDistance(p)<<" "<<getDistance(_data, p.GetData())<<endl; 
          if (GetSAXDistance(p) > getDistance(_data, p.GetData())) {
               cout<<"BIG ERROR SAX"<<endl;
               for (int j = 0; j< 10; ++j)
                    cout<<p.Getsax()[j]<<" ";
               
               cout<<endl;
               for (int j = 0; j< 10; ++j)
                    cout<<_sax[j]<<" ";   
               
               exit(1);
           }
           
          if (GetSAXDistance(p)>_answer._distMax) {
               countfiltered++;
               continue; //filter
          }
          float dist = getDistance(p.GetData(), _data);
          _answer.CheckAndAdd(_indices[i],dist);
     } 
     cout<<"filtered "<<countfiltered<<endl;
     _isFinished = 1;
}
