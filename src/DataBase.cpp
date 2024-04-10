#include "DataBase.hpp"
#include <fstream>
#include "assert.h"
#include <iostream>
#include "Utils.hpp"

using namespace std;

DataBase::DataBase(const char* filename) {     
     ifstream ifs;
     ifs.open(filename, std::ios::binary);
     assert(ifs.is_open());
     
     uint32_t N;  // num of points
     ifs.read((char *)&N, sizeof(uint32_t));
     for (int i = 0; i < N; ++i){
          DataPoint p(ifs);
          _data_points.push_back(p);
     }
     _countPoints = N;
}

DataBase::~DataBase() {
}

std::vector<DataPoint>& DataBase::GetPoints(){
    return _data_points;
}


DataPoint& DataBase::GetPoint(int index) {
    return _data_points[index];
}

int DataBase::GetSize() {
    return _countPoints;
}

int DataBase::isGreaterByCatAndTS(int i, int j){
     if (_data_points[i].GetC()>_data_points[j].GetC() || (_data_points[i].GetC()==_data_points[j].GetC() && _data_points[i].GetTS()>_data_points[j].GetTS()))
          return 1;
     return 0;
}

void DataBase::SiftByCatAndTS(int i, int n){
     while (1) {
          int indmax = i;
          if (2*i+1<=n && isGreaterByCatAndTS(_sortedIndByCatAndTS[2*+1], _sortedIndByCatAndTS[indmax]))
               indmax = 2*i+1;
          if (2*i+2<=n && isGreaterByCatAndTS(_sortedIndByCatAndTS[2*+2], _sortedIndByCatAndTS[indmax]))
               indmax = 2*i+2;
          if (indmax == i) break;
          swapIndices(_sortedIndByCatAndTS, indmax, i);
          i = indmax;
     } 
}

void DataBase::SortByCatAndTS() {
     _sortedIndByCatAndTS = new int[_countPoints];
     for (int i = 0; i<_countPoints; ++i)
          _sortedIndByCatAndTS[i] = i;
     
     for (int i =_countPoints/2; i>=0; i--)
          SiftByCatAndTS(i,_countPoints);
     
     for (int i = _countPoints-1; i>=1; i--) {
         swapIndices(_sortedIndByCatAndTS, 0, i);
         SiftByCatAndTS(0,i-1);
     }
}


