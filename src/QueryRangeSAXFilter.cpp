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
          float saxDistance = _db.GetSAXDistance(p.Getsax(), _sax);

#ifdef FILTERCOUNT
          float realDistance = getDistance(p.GetData(), _data);
          float paaDistance = getPaaDistance(_paa, p.GetPaa())*_db._scaleFactor;
        
          
          
          if (realDistance >_answer._distMax) { //should be filtered
               countShouldBeFiltered ++;  
               if (paaDistance>_answer._distMax) 
                    countFilteredByPaa ++;
               if (saxDistance>_answer._distMax) 
                    countFilteredBySAX ++; 
               continue;
          }        
#endif  
          if (saxDistance >_answer._distMax) continue;
          float realDistance = getDistance(p.GetData(), _data);
          _answer.CheckAndAdd(_indices[i],realDistance);
     } 
#ifdef FILTERCOUNT
     cout<<"filtered by PAA "<<countFilteredByPaa<<" and by SAX "<<countFilteredBySAX<<" out of "<<countShouldBeFiltered<<endl;
#endif
     _isFinished = 1;
}
