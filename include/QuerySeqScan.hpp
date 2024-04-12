#ifndef _QUERYSEQSCAN_H
#define _QUERYSEQSCAN_H

#include "Query.hpp"

class QuerySeqScan: public Query {
public:
     QuerySeqScan(std::ifstream& ifs, const DataBase& db);
     ~QuerySeqScan();
     
     virtual void run (int& switchquery); 
};


#endif
