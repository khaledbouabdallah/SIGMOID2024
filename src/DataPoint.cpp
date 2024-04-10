#include "DataPoint.hpp"
#include "globals.hpp"
#include <fstream>

using namespace std;

DataPoint::DataPoint(ifstream& ifs){
     _data = new float[DATA_SIZE];
     ifs.read((char *)&_c, sizeof(int));
     ifs.read((char *)&_timestamp, sizeof(float));
     ifs.read((char *)_data, DATA_SIZE * sizeof(float));
}

float DataPoint::GetTS() const {
     return _timestamp;
}

int DataPoint::GetC() const {
     return _c;
}

float* DataPoint::GetData() const {
     return _data;
}

DataPoint::~DataPoint(){
     delete[] _data;
}


