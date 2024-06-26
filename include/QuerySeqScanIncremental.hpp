#ifndef _QUERYSEQSCANINCREMENTAL_HPP
#define _QUERYSEQSCANINCREMENTAL_HPP

#include "Query.hpp"

class QuerySeqScanIncremental: public Query {
public:
     int _nextPointIndice;
public:
     QuerySeqScanIncremental(std::ifstream& ifs, const DataBase& db);
     ~QuerySeqScanIncremental();
     
     virtual void run (int& switchquery); 
     
     void PrintDelta();
};


#endif
