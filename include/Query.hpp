#ifndef _QUERY_HPP
#define _QUERY_HPP

#include <fstream>
#include "Answer.hpp"

class DataBase;
class DataPoint;

class Query {

protected:
     int _type;
     int _c; 
     float _tsr;
     float _tsl;
     float* _data; 
     
     int* _indices;
     int _startIndice;
     int _endIndice;
     
     Answer _answer;
     const DataBase& _db;
     
     int _isFinished;
     
public:
     Query(std::ifstream& ifs, const DataBase& db);
     
     ~Query();
        
     void WriteOutput(std::ofstream& ofs);
     
     int IsValid(const DataPoint& p) const;

     virtual void run (int& switchquery) = 0;   
     
     int IsFinished();  
     
     inline float* GetData() {return _data;}
     
     float GetSAXDistance(const DataPoint& p);
     
protected:

     void InitIndicesAndRanges();

     void InitAnswerWithRanges();
};

#endif

