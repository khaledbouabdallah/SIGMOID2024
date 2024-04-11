#include "DataBase.hpp"
#include <fstream>
#include "assert.h"
#include <iostream>
#include "Utils.hpp"
#include <cmath>

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
     cout<<_countPoints<<endl;
}

DataBase::~DataBase() {
     //cleanup indices
     delete[] _sortedIndByCatAndTS;
     delete[] _sortedIndByTS;
     delete[] _sortedIndNormal;
     
     //cleanup category data
     delete[] _catstart;
     delete[] _catend;
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
     if ((_data_points[i].GetC()>_data_points[j].GetC()) || (_data_points[i].GetC()==_data_points[j].GetC() && _data_points[i].GetTS()>_data_points[j].GetTS()))
          return 1;
     return 0;
}

void DataBase::SiftByCatAndTS(int i, int n){
     while (1) {
          int indmax = i;
          if (2*i+1<n && isGreaterByCatAndTS(_sortedIndByCatAndTS[2*i+1], _sortedIndByCatAndTS[indmax]))
               indmax = 2*i+1;
          if (2*i+2<n && isGreaterByCatAndTS(_sortedIndByCatAndTS[2*i+2], _sortedIndByCatAndTS[indmax]))
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
     
     /*
     for (int i = 0; i<_countPoints-1; ++i) {
         DataPoint& dp1 = _data_points[_sortedIndByCatAndTS[i]];
         DataPoint& dp2 = _data_points[_sortedIndByCatAndTS[i+1]];
         if (dp1.GetC()>dp2.GetC())
               cout<<"not sorted by cat"<<endl;
         else if (dp1.GetC() == dp2.GetC() && dp1.GetTS()>dp2.GetTS())
                cout<<"not sorted by ts"<<endl;
     }
     
     */
     
     //first count categories, so as to allocate properly the arrays
     _countCategories = 0;
     int i=0;
     while (i<_countPoints) {
          _countCategories++;
          i++;
          while (i<_countPoints && _data_points[_sortedIndByCatAndTS[i]].GetC() == _data_points[_sortedIndByCatAndTS[i-1]].GetC())
               i++;
     }
     cout<<_countCategories<<endl;
     
     //now set start / end range for each category
     _catstart = new int[_countCategories];
     _catend = new int[_countCategories];
     
      i=0;
      while (i<_countPoints) {
          int crtcat = _data_points[_sortedIndByCatAndTS[i]].GetC();
          _catstart[crtcat] = i;
          i++;
          while (i<_countPoints && _data_points[_sortedIndByCatAndTS[i]].GetC() == _data_points[_sortedIndByCatAndTS[i-1]].GetC())
               i++;
          _catend[crtcat] = i-1;
     }
}

void DataBase::SortByTS() {
     _sortedIndByTS = new int[_countPoints];
     for (int i = 0; i<_countPoints; ++i)
          _sortedIndByTS[i] = i;
}


int* DataBase::GetIndicesSortedByCatAndTS() {
     return _sortedIndByCatAndTS;
}

   
int* DataBase::GetNormalIndices(){
     return _sortedIndNormal;
}
     
     
int* DataBase::GetIndicesSortedByTS() {
     return _sortedIndByTS;
}

void DataBase::GetCatRange(int cat, int& start, int& end) {
     start = _catstart[cat];
     end = _catend[cat];
}
     
void DataBase::GetTSRange(int lts, int rts, int& start, int& end) {
//TODO
     start = 0;
     end = _countPoints;
}
     
void DataBase::GetCatAndTSRange(int cat, int rts, int& start, int& end) {
//TODO
     start = _catstart[cat];
     end = _catend[cat];
}

void DataBase::ComputeMeans() {

     _means = new float[DATA_SIZE];
     
     // loop over all dimensions
     for (int i = 0; i<DATA_SIZE; ++i) {
          float sum = 0;
          for (int j = 0; j<_countPoints; ++j) {
               sum += _data_points[j].GetData()[i];
          }
          _means[i] = sum/_countPoints;
     }

}

void DataBase::ComputeStds() {

     _stds = new float[DATA_SIZE];
     
     // loop over all dimensions
     for (int i = 0; i<DATA_SIZE; ++i) {
          float sum = 0;
          for (int j = 0; j<_countPoints; ++j) {
               sum += (_data_points[j].GetData()[i] - _means[i])*(_data_points[j].GetData()[i] - _means[i]);
          }
          _stds[i] = sqrt(sum/_countPoints);
     }

}

void DataBase::NormalizeData() {

     ComputeMeans();
     ComputeStds();

     for (int i = 0; i<_countPoints; ++i) {
          float* data = _data_points[i].GetData();
          for (int j = 0; j<DATA_SIZE; ++j) {
               data[j] = (data[j] - _means[j])/_stds[j];
          }
     }

}
