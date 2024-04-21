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
          //cout<<p.GetPaa()[0]<<endl;
          //cout<<GetSAXDistance(p)<<" "<<getPaaDistance(_paa, p.GetPaa())*_db._scaleFactor<<" "<<getDistance(_data, p.GetData())<<endl; 
          /*
          if (GetSAXDistance(p) > getDistance(_data, p.GetData())) {
               cout<<"BIG ERROR SAX"<<endl;
               for (int j = 0; j< 10; ++j)
                    cout<<p.Getsax()[j]<<" ";
               
               cout<<endl;
               for (int j = 0; j< 10; ++j)
                    cout<<_sax[j]<<" ";   
               
               exit(1);
           }*/
          
          //cout<< GetPAADistance(_paa, p.GetPaa())*_db._scaleFactor) <<" "<<getDistance(_data, p.GetData()<<endl;
          float realDistance = getDistance(p.GetData(), _data);
          float paaDistance = getPaaDistance(_paa, p.GetPaa())*_db._scaleFactor;
          float saxDistance = GetSAXDistance(p);
          
          if (realDistance >_answer._distMax) { //should be filtered
               countShouldBeFiltered ++;  
               if (paaDistance>_answer._distMax) 
                    countFilteredByPaa ++;
               if (saxDistance>_answer._distMax) 
                    countFilteredBySAX ++; 
               continue;
          }          
          
          _answer.CheckAndAdd(_indices[i],realDistance);
     } 
     cout<<"filtered by PAA "<<countFilteredByPaa<<" and by SAX "<<countFilteredBySAX<<" out of "<<countShouldBeFiltered<<endl;
     _isFinished = 1;
}
