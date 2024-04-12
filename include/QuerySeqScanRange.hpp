#ifndef _QUERYSEQSCANRANGE_HPP
#define _QUERYSEQSCANRANGE_HPP

#include "Query.hpp"

class QuerySeqScanRange: public Query {
public:
     QuerySeqScanRange(std::ifstream& ifs, const DataBase& db);
     ~QuerySeqScanRange();
     
     virtual void run (int& switchquery); 
};


#endif
