#include "DataBase.hpp"
#include <fstream>
#include "assert.h"

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
}

std::vector<DataPoint>& DataBase::GetPoints(){
    return _data_points;
}


DataPoint& DataBase::GetPoint(int index) {
    return _data_points[index];
}

int DataBase::GetSize() {
    return _data_points.size();
}


DataBase::~DataBase() {
}
