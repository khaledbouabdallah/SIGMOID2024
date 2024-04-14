#include "DataBase.hpp"
#include <fstream>
#include "assert.h"
#include <iostream>
#include "Utils.hpp"
#include <cmath>

using namespace std;

DataBase::DataBase(const char* filename):_catstart(NULL), _catend(NULL)  {     
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
     _sortedIndNormal = new int[_countPoints];
     _sortedIndByCatAndTS = new int[_countPoints];
     _sortedIndByTS = new int[_countPoints];
     for (int i = 0; i<_countPoints; ++i)
          _sortedIndByTS[i] = _sortedIndNormal[i] = _sortedIndByCatAndTS[i] = i;
}

DataBase::~DataBase() {
     //cleanup indices
     delete[] _sortedIndByCatAndTS;
     delete[] _sortedIndByTS;
     delete[] _sortedIndNormal;
     
     //cleanup category data
     if (_catstart)
          delete[] _catstart;
     if (_catend)
          delete[] _catend;
}

std::vector<DataPoint>& DataBase::GetPoints(){
    return _data_points;
}


const DataPoint& DataBase::GetPoint(int index) const {
    return _data_points[index];
}

int DataBase::GetSize() const {
    return _countPoints;
}

int DataBase::CompareByCatAndTS(const DataPoint& p1, const DataPoint& p2){
     if ((p1.GetC()>p2.GetC()) || (p1.GetC()==p2.GetC() && p1.GetTS()>p2.GetTS()))
          return 1;
     return 0;
}

int DataBase::CompareByTS(const DataPoint& p1, const DataPoint& p2){
     if (p1.GetTS()>p2.GetTS())
          return 1;
     return 0;
}

void DataBase::SwapIndices(int* indicesArray, int ind1, int ind2) {
     int aux = indicesArray[ind1]; 
     indicesArray[ind1] = indicesArray[ind2];
     indicesArray[ind2] = aux;
}

void DataBase::SiftIndices(int* indices, int i, int n, int (*funccomp)(const DataPoint&, const DataPoint&)){
     while (1) {
          int indmax = i;
          if (2*i+1<n && funccomp(_data_points[indices[2*i+1]], _data_points[indices[indmax]]))
               indmax = 2*i+1;
          if (2*i+2<n && funccomp(_data_points[indices[2*i+2]], _data_points[indices[indmax]]))
               indmax = 2*i+2;
          if (indmax == i) break;
          SwapIndices(indices, indmax, i);
          i = indmax;
     } 
}

void DataBase::Sort(int* indices, int (*funccomp)(const DataPoint&, const DataPoint&)) {
     for (int i =_countPoints/2; i>=0; i--)
          SiftIndices(indices,i,_countPoints,funccomp);
          
     //check
     /*
     for (int i = 0; i<_countPoints/2; ++i) {
         DataPoint& dp1 = _data_points[indices[i]];
         if (2*i+1>=_countPoints) continue; 
         DataPoint& dp2 = _data_points[indices[2*i+1]];
         if (funccomp(dp2,dp1)) cout<<"error child left"<<endl;
         if (2*i+2>=_countPoints) continue; 
         DataPoint& dp3 = _data_points[indices[2*i+1]];
         if (funccomp(dp3,dp1)) cout<<"error child right"<<endl;
     }
     */

     for (int i = _countPoints-1; i>=1; i--) {
         SwapIndices(indices, 0, i);
         SiftIndices(indices,0,i,funccomp);
     }
     
     //check
     /*
     for (int i = 0; i<_countPoints-1; ++i) {
         DataPoint& dp1 = _data_points[indices[i]];
         DataPoint& dp2 = _data_points[indices[i+1]];
         if (funccomp(dp1, dp2)) {
               cout<<"not sorted"<<endl;
               cout<<dp1.GetTS()<<endl;
               cout<<dp2.GetTS()<<endl;
         }
     }
     */
}

void DataBase::SortByCatAndTS() {
     Sort(_sortedIndByCatAndTS, CompareByCatAndTS);
}

void DataBase::ProcessCategories() {
     //count categories, so as to allocate properly the arrays
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
     Sort(_sortedIndByTS, CompareByTS);
}


int* DataBase::GetIndicesSortedByCatAndTS() const {
     return _sortedIndByCatAndTS;
}

   
int* DataBase::GetNormalIndices() const {
     return _sortedIndNormal;
}
     
     
int* DataBase::GetIndicesSortedByTS() const {
     return _sortedIndByTS;
}

void DataBase::GetCatRange(int cat, int& start, int& end) const {
     assert (cat<_countCategories);
     start = _catstart[cat];
     end = _catend[cat]+1;
}
     
int DataBase::GetFirstPositionGE(float ts, int* indices, int start, int end) const {
     /*int i = start;
     while (ts>_data_points[indices[i]].GetTS())
          i++;
     */

     // the range from start to end (inc start, exc end) is sorted by ts
     while (start<end) {
          int mid = (start+end)/2;
          if (ts>_data_points[indices[mid]].GetTS()) 
               start = mid+1;
          else
               end = mid;
     }
     
   
     int toreturn = end;
     /*if (i!=toreturn)
          cout<<"ERROR"<<" "<<i<<" "<<toreturn<<endl;*/
     return toreturn;
}

int DataBase::GetLastPositionLE(float ts, int* indices, int start, int end) const {
     // the range from start to end (inc start, exc end) is sorted by ts
     
     /* int i = end-1;
     while (ts<_data_points[indices[i]].GetTS())
          i--;
     */
     while (start<end) {
          int mid = (start+end)/2;
          if (ts>=_data_points[indices[mid]].GetTS()) 
               start = mid+1;
          else
               end = mid;
     }
          
     int toreturn = start-1;
     /*if (i!=toreturn)
          cout<<"ERROR"<<" "<<i<<" "<<toreturn<<endl;*/
     return toreturn;
     
}
     
void DataBase::GetTSRange(float lts, float rts, int& start, int& end) const {
     start = GetFirstPositionGE(lts, _sortedIndByTS, 0, _countPoints);    
     end = GetLastPositionLE(rts, _sortedIndByTS, 0, _countPoints)+1; 
}
     
void DataBase::GetCatAndTSRange(int cat, float lts, float rts, int& start, int& end) const {
     assert (cat<_countCategories);
     start = GetFirstPositionGE(lts, _sortedIndByCatAndTS, _catstart[cat], _catend[cat]+1);    
     end = GetLastPositionLE(rts, _sortedIndByCatAndTS, _catstart[cat], _catend[cat]+1)+1;  
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
