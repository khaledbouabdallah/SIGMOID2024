#include "QuerySeqScanRangeIncremental.hpp"
#include "Utils.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"
#include <iostream>

using namespace std;

QuerySeqScanRangeIncremental::QuerySeqScanRangeIncremental(std::ifstream& ifs, const DataBase& db) : Query(ifs,db) {
     InitIndicesAndRanges();
     InitAnswerWithRanges();
     _nextPointIndice = _startIndice+DATA_SIZE;
}

QuerySeqScanRangeIncremental::~QuerySeqScanRangeIncremental(){
}

void QuerySeqScanRangeIncremental::run (int& switchquery){
     while(1) {
          //cout<<_nextPointIndice;
          if (_nextPointIndice>=_endIndice) {
               _isFinished = 1;
               break;
          }
          //examine one point
          const DataPoint& p = _db.GetPoint(_indices[_nextPointIndice]);
          float dist = getDistance(p.GetData(), _data);
          _answer.CheckAndAdd(_indices[_nextPointIndice],dist);
          
          //save next point indice
          _nextPointIndice++;
          //check that I can run some more
          if (switchquery || done)
               break;
     } 
}

void QuerySeqScanRangeIncremental::PrintDelta(){
     cout<<"remaining "<<_endIndice-_nextPointIndice<<endl;
}
