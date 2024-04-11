#ifndef _QUERY_HPP
#define _QUERY_HPP

#include <fstream>
#include "Answer.hpp"

class DataBase;

class Query {

protected:
     int _type;
     int _c; 
     float _tsr;
     float _tsl;
     float* _data; 
     
     Answer _answer;
     const DataBase& _db;
     
public:
     Query(std::ifstream& ifs, const DataBase& db);
     
     virtual void run (int& switchquery);
     
     ~Query();
};

#endif

