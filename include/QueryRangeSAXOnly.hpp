#ifndef _QUERYRANGESAXONLY_HPP
#define _QUERYRANGESAXONLY_HPP

#include "Query.hpp"

class QueryRangeSAXOnly: public Query {
public:
     QueryRangeSAXOnly(std::ifstream& ifs, const DataBase& db);
     ~QueryRangeSAXOnly();
     
     virtual void run (int& switchquery); 
};


#endif
