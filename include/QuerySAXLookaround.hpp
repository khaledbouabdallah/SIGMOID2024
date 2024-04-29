#ifndef _QUERYSAXLOOKAROUND_H
#define _QUERYSAXLOOKAROUND_H

#include "Query.hpp"
#include "IndexSAXTrie.hpp"


class QuerySAXLookaround: public Query {
private:
     IndexSAXTrie* _index;
public:
     QuerySAXLookaround(std::ifstream& ifs, const DataBase& db);
     ~QuerySAXLookaround();
     
     virtual void run (int& switchquery); 
     
     inline void SetIndex(IndexSAXTrie* index) {_index = index;}
private:
     void ScanIndex(Node* node, int level, float crtDist);
     
     int _examined;
     int _found;
};


#endif
