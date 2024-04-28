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
     int countFilteredBySAX = 0;
     int countFilteredByPaa = 0;
     int countShouldBeFiltered = 0;
     for (int i = _startIndice+DATA_SIZE; i< _endIndice; ++i) {
          const DataPoint& p = _db.GetPoint(_indices[i]);
          
//#define FILTERCOUNT
#ifdef FILTERCOUNT
          {
               cout<<_db.GetSAXDistance(p.Getsax(), _sax)<<" "<<getDistance(_data, p.GetData())<<endl; 
          }        
#endif

          float saxDistance = _db.GetSAXDistance(p.Getsax(), _sax); 
          if (saxDistance >_answer._distMax) continue;
          float realDistance = getDistance(p.GetData(), _data);
          
          if (saxDistance > realDistance) {
               cout<<"BIG ERROR SAX"<<endl;
               for (int j = 0; j< 10; ++j)
                    cout<<p.Getsax()[j]<<" ";
               
               cout<<endl;
               for (int j = 0; j< 10; ++j)
                    cout<<_sax[j]<<" ";   
               
               exit(1);
           }
          
          _answer.CheckAndAdd(_indices[i],realDistance);
     } 

     _isFinished = 1;
}

          
        
