#include "../include/IndexSAXTrie.hpp"
#include "../include/DataBase.hpp"
#include "../include/DataPoint.hpp"
#include <iostream>

using namespace std;

IndexSAXTrie::IndexSAXTrie(const DataBase& db): _db(db), _countNodes(0) {  
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
               //if (crtNode->_childValues.size()>5)
               //     cout<<j<<" "<<crtNode->_childValues.size()<<endl;
               uint64_t crtCode = sax[j];
               Node* nextNode = crtNode->_childNodes[crtCode];
               if (!nextNode) {
                    nextNode = new Node();
                    _countNodes++;
                    crtNode->_childNodes[crtCode] = nextNode;
                    crtNode->_childValues.push_back(crtCode);
               }
               crtNode = nextNode;
          }
          crtNode->_childValues.push_back(i); //last we put indices
     }
     
     cout<<"node count index: "<<_countNodes<<endl;
            
}

vector<int>* IndexSAXTrie::getPointIndices(uint64_t* sax){
     Node* crtnode = _root;
     for (int i = 0; i< DATA_SIZE-1; ++i) {
          crtnode = crtnode-> _childNodes[sax[i]];
          if (crtnode == NULL) return NULL;
     }
     return &(crtnode->_childValues);
}


