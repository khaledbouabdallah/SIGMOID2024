#ifndef _QUERYIVF_H
#define _QUERYIVF_H

#include "Query.hpp"
#include "IndexIVF.hpp"  

class QueryIVF: public Query {
public:
     QueryIVF(std::ifstream& ifs, const IndexIVF& ivf);
     ~QueryIVF();
     
     virtual void run (int& switchquery); 
};


#endif
