#ifndef _QUERY_HPP
#define _QUERY_HPP

#include <fstream>
#include "Answer.hpp"
#include <vector>

class DataBase;
class DataPoint;

class Query {

protected:
     int _type;
     int _c; 
     float _tsr;
     float _tsl;
     float* _data; 
     uint64_t* _sax; 
     float* _paa;
     
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
     
     inline float* GetPaa() {return _paa;}
     
     inline void SetPaa(float* paa) {_paa = paa;}
     
     void SetSAX(uint64_t* sax);
     
     void CheckIndices(const std::vector<int>& indices);
     
     
protected:

     void InitIndicesAndRanges();

     void InitAnswerWithRanges();
};

#endif

