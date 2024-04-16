#ifndef _QUERYSEQSCANRANGEINCREMENTAL_HPP
#define _QUERYSEQSCANRANGEINCREMENTAL_HPP

#include "Query.hpp"

class QuerySeqScanRangeIncremental: public Query {
public:
     int _nextPointIndice;

public:
     QuerySeqScanRangeIncremental(std::ifstream& ifs, const DataBase& db);
     ~QuerySeqScanRangeIncremental();
     
     virtual void run (int& switchquery); 
     
     void PrintDelta();
};


#endif
