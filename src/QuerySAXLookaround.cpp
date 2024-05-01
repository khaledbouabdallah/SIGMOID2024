#include "../include/QuerySAXLookaround.hpp"
#include "../include/IndexSAXTrie.hpp"
#include "../include/DataPoint.hpp"
#include "../include/DataBase.hpp"
#include "../include/Utils.hpp"
#include <iostream>

QuerySAXLookaround::QuerySAXLookaround(std::ifstream& ifs, const DataBase& db) : Query(ifs,db), _examined(0), _found(0){
}

QuerySAXLookaround::~QuerySAXLookaround(){
}

void QuerySAXLookaround::run (int& switchquery){
    //cout<<"running query "<<endl;
    ScanIndex(_index->_root, 0, 0);
    cout<<_examined<<endl;
    _isFinished = 1;
}



void QuerySAXLookaround::ScanIndex(Node* node, int level, float crtDist){  
  
       
     if (level == DATA_SIZE){
          for (int i = 0; i<node->_childValues.size(); ++i)
               if (IsValid(_db.GetPoint(node->_childValues[i]))) {
                    _answer.CheckAndAdd(node->_childValues[i],0);
                    _found++;
               }
          _examined+=node->_childValues.size();
          return;
     }
     
     if (_examined>1000 || _examined>=_db.GetSize()) return;
     
     uint64_t crtsax = _sax[level];
     
    //bin search this value in child values
    //to find the largest pos <=
     int first = 0;
     int last = node->_childValues.size()-1;
     while (first<=last) {
          int mid = (first+last)/2;
          if (node->_childValues[mid]<=crtsax)
               first = mid+1;
          else
               last = mid-1;
     }
     cout<<first-1<<endl;
     int dif = first-1;
     if (node->_childValues.size()-first>dif)
          dif = node->_childValues.size()-first;
      
     //try left and right
     for (int i = 1; i<=dif; ++i){
          int ind = first-1-i;
          if (ind>=0)
               ScanIndex(node->_childNodes[node->_childValues[ind]], level+1, crtDist);
          ind = first-1+i;
          if (ind<node->_childValues.size())
               ScanIndex(node->_childNodes[node->_childValues[ind]], level+1, crtDist);
     }
          
          
          
}
