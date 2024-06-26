#include "../include/DataBase.hpp"
#include <fstream>
#include "assert.h"
#include <iostream>
#include "../include/Utils.hpp"
#include <cmath>
#include "../include/SortUtils.hpp"
#include "../include/SAX.hpp"
#include <cstring>

using namespace std;

DataBase::DataBase(const char* filename):_catstart(NULL), _catend(NULL), _categories(NULL), _globalMean(0), _globalStd(1)  {  
     
   
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

const std::vector<DataPoint>& DataBase::GetPoints() const{
    return _data_points;
}

const DataPoint& DataBase::GetPoint(int index) const {
    return _data_points[index];
}

int DataBase::GetSize() const {
    return _countPoints;
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
     
     //now set start / end range for each category
     _catstart = new int[_countCategories];
     _catend = new int[_countCategories];
     
     _categories = new int[_countCategories];
     
      i=0;
      int indcat=0;
     
      while (i<_countPoints) {
           _categories[indcat] = _data_points[_sortedIndByCatAndTS[i]].GetC();
           _catstart[indcat] = i;
          i++;
          while (i<_countPoints && _data_points[_sortedIndByCatAndTS[i]].GetC() == _data_points[_sortedIndByCatAndTS[i-1]].GetC())
               i++;
          _catend[indcat] = i-1;
          indcat++;
     }
}

void DataBase::SortByCatAndTS() {
     SortIndices(_sortedIndByCatAndTS, _data_points, _countPoints, CompareByCatAndTS);
}

void DataBase::SortByTS() {
     SortIndices(_sortedIndByTS, _data_points, _countPoints, CompareByTS);
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

int DataBase::GetIndCat(int cat) const{
     int start = 0;
     int end = _countCategories;
     while (start<end) {
          int mid = (start+end)/2;
          if (cat == _categories[mid]) return mid;
          else if (cat < _categories[mid]) end = mid;
          else start = mid+1;
     }
     cout<<"big error "<<cat<<" "<<_countCategories<<endl;
     return -1;
}

void DataBase::GetCatRange(int cat, int& start, int& end) const {
     //assert (cat<_countCategories);
     int indcat = GetIndCat(cat);
     start = _catstart[indcat];
     end = _catend[indcat]+1;
}
     
void DataBase::GetTSRange(float lts, float rts, int& start, int& end) const {
     start = GetFirstPositionGETS(lts, _sortedIndByTS, _data_points, 0, _countPoints);    
     end = GetLastPositionLETS(rts, _sortedIndByTS,  _data_points, 0, _countPoints)+1; 
}
     
void DataBase::GetCatAndTSRange(int cat, float lts, float rts, int& start, int& end) const {
     assert (cat<_countCategories);
     start = GetFirstPositionGETS(lts, _sortedIndByCatAndTS,  _data_points,  _catstart[cat], _catend[cat]+1);    
     end = GetLastPositionLETS(rts, _sortedIndByCatAndTS,  _data_points, _catstart[cat], _catend[cat]+1)+1;  
}

void DataBase::ComputeSAXStuff() {
     //first, compute global mean and std
     ComputeGlobalMean();
     ComputeGlobalStd();

     //then, create SAX maker
     SAX saxmaker(PAA_SEGMENTS, SAX_CARD, _globalMean, _globalStd);
     
     //finaly, compute sax rep 
     for (int i = 0; i < _countPoints; ++i){
          DataPoint& p = _data_points[i];        
          //float* paa = saxmaker.ToPAA(p.GetData(), DATA_SIZE);
          //p.SetPaa(paa);
          uint64_t* sax = saxmaker.ToSAX(p.GetData(), DATA_SIZE);  //this is overall sax, no paa
          p.Setsax(sax);
     }
     
     //and compute breakpoint distances
     _breakpoints = getBreakPoints(SAX_CARD, _globalMean, _globalStd);
      //_scaleFactor = sqrt((float)DATA_SIZE/(float)PAA_SEGMENTS);
      //_scaleFactor = (float)DATA_SIZE/(float)PAA_SEGMENTS;
     _scaleFactor = 1;
     ComputeSaxDistances();
}

void DataBase::ComputeSaxDistances(){
     memset(_saxDistances, 0, 256*256*sizeof(float));
     for (int i = 0; i< SAX_CARD; ++i)
          for (int j = i+2; j<SAX_CARD;j++) {
               _saxDistances[i][j] = _breakpoints[j-1]-_breakpoints[i];
               _saxDistances[i][j] =  _scaleFactor *(_saxDistances[i][j]*  _saxDistances[i][j]);
               _saxDistances[j][i] =  _saxDistances[i][j];
          }     
}

float DataBase::GetSAXDistance(uint64_t* sax1, uint64_t* sax2) const{
    float sum = 0;
    for (int i = 0; i< PAA_SEGMENTS; ++i)
          sum+=_saxDistances[sax1[i]][sax2[i]];
    return sum;  
}

void DataBase::ComputeGlobalMean() {
     _globalMean = 0;
     for (int i = 0; i<DATA_SIZE; ++i) 
          for (int j = 0; j<_countPoints; ++j) 
               _globalMean += _data_points[j].GetData()[i];

      _globalMean /= (float)(_countPoints*DATA_SIZE);

}

void DataBase::ComputeGlobalStd() {
     _globalStd = 0;
     for (int i = 0; i<DATA_SIZE; ++i) 
          for (int j = 0; j<_countPoints; ++j) 
               _globalStd += (_data_points[j].GetData()[i] - _globalMean)*(_data_points[j].GetData()[i] - _globalMean);
     _globalStd = sqrt(_globalStd / ((float)(_countPoints*DATA_SIZE)));
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

void DataBase::NormalizeData_Axis1() {

     ComputeMeans();
     ComputeStds();

     for (int i = 0; i<_countPoints; ++i) {
          float* data = _data_points[i].GetData();
          for (int j = 0; j<DATA_SIZE; ++j) {
               data[j] = (data[j] - _means[j])/_stds[j];
          }
     }

}

void DataBase::NormalizeData_Axis0() {

     for (int i = 0; i<_countPoints; ++i) {
          float* data = _data_points[i].GetData();
          float mean = calculateMean(data, DATA_SIZE);
          float std = calculateStd(data, DATA_SIZE, mean);

          for (int j = 0; j<DATA_SIZE; ++j) {
               data[j] = (data[j] - _means[j])/_stds[j];
          }
        
     }

}

void DataBase::NormalizeData_Global() {

     for (int i = 0; i<_countPoints; ++i) {
          float* data = _data_points[i].GetData();
          for (int j = 0; j<DATA_SIZE; ++j) {
               data[j] = (data[j] - _globalMean)/_globalStd;
          }
     }

}

void DataBase::PrintColumnsData() {
     ComputeMeans();
     ComputeStds();
     for (int i = 0; i<DATA_SIZE; ++i) 
          cout<<_means[i]<<" "<<_stds[i]<<endl;
}


