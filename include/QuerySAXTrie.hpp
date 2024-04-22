#ifndef _QUERYSAXTRIE_H
#define _QUERYSAXTRIE_H

#include "Query.hpp"
#include "IndexSAXTrie.hpp"


class QuerySAXTrie: public Query {
private:
     IndexSAXTrie* _index;
public:
     QuerySAXTrie(std::ifstream& ifs, const DataBase& db);
     ~QuerySAXTrie();
     
     virtual void run (int& switchquery); 
     
     inline void SetIndex(IndexSAXTrie* index) {_index = index;}
private:
     void ScanIndex(Node* node, int level, float crtDist);
};


#endif
