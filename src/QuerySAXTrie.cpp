#include "QuerySAXTrie.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"
#include "Utils.hpp"
#include <iostream>

QuerySAXTrie::QuerySAXTrie(std::ifstream& ifs, const DataBase& db) : Query(ifs,db){
}

QuerySAXTrie::~QuerySAXTrie(){
}

void QuerySAXTrie::run (int& switchquery){
    ScanIndex(_index->_root, 0, 0);
}

void QuerySAXTrie::ScanIndex(Node* node, int level, float crtDist){
     if (level == PAA_SEGMENTS) {
          CheckIndices(node->_childValues);
          return;
     }
     for (int val: node->_childValues) {
          float dist = crtDist + _db._saxDistances[val][_sax[level]];
          if (dist>_answer._distMax) continue;
          ScanIndex(node->_childNodes[val], level+1, dist);
     }
          
}
