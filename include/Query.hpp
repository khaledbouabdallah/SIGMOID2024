#ifndef _QUERY_HPP
#define _QUERY_HPP

#include <fstream>

class Query {

protected:
     int _c; 
     float _tsr;
     float _tsl;
     float* _data; 
public:
     Query(std::ifstream& ifs);
     
     virtual void run (int& switchquery) = 0;
     
     ~Query();
};

#endif

