#include "IndexSAXTrie.hpp"
#include "DataBase.hpp"
#include "DataPoint.hpp"
#include <iostream>

using namespace std;

IndexSAXTrie::IndexSAXTrie(const DataBase& db): _db(db) {  
     _root = new Node(); 
}

IndexSAXTrie::~IndexSAXTrie(){
}

void IndexSAXTrie::BuildIndex() {
//TODO
     int nPoints = _db.GetSize();
     
     for (int i = 0; i < nPoints; ++i) {
          const DataPoint& p = _db.GetPoint(i);
          uint64_t* sax = p.Getsax();
          
          Node* crtNode = _root;
          for (int j = 0; j < PAA_SEGMENTS; ++j) {
               if (crtNode->_childValues.size()>5)
                    cout<<j<<" "<<crtNode->_childValues.size()<<endl;
               uint64_t crtCode = sax[j];
               Node* nextNode = crtNode->_childNodes[crtCode];
               if (!nextNode) {
                    nextNode = new Node();
                    crtNode->_childNodes[crtCode] = nextNode;
                    crtNode->_childValues.push_back(crtCode);
               }
               crtNode = nextNode;
          }
          crtNode->_childValues.push_back(i); //last we put indices
     }
            
}


