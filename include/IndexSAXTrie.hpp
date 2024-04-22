#ifndef _INDEXSAXTRIE_H
#define _INDEXSAXTRIE_H

#include "globals.hpp"
#include <vector>
#include <cstring>
class DataBase;

using namespace std;

class Node {
public:
     Node* _childNodes[256];
     vector<int> _childValues;
public:
     inline Node() {memset(_childNodes, 0, 256*sizeof(void*)); };
};

class IndexSAXTrie {
public:
     Node* _root;
     const DataBase& _db; 
public:
     IndexSAXTrie(const DataBase& db);
     ~IndexSAXTrie();
     
     void BuildIndex();  
    
     inline Node* getRoot() {return _root;}
  
};

#endif
