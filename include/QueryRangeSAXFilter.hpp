#ifndef _QUERYRANGESAXFILTER_HPP
#define _QUERYRANGESAXFILTER_HPP

#include "Query.hpp"

class QueryRangeSAXFilter: public Query {
public:
     QueryRangeSAXFilter(std::ifstream& ifs, const DataBase& db);
     ~QueryRangeSAXFilter();
     
     virtual void run (int& switchquery); 
};


#endif
