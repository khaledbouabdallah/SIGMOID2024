#include "DataPoint.hpp"
#include "globals.hpp"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

DataPoint::DataPoint(ifstream& ifs){
     _data = new float[100];
     ifs.read((char *)&_c, sizeof(uint32_t));
     ifs.read((char *)&_timestamp, sizeof(uint32_t));
     ifs.read((char *)_data, 100 * sizeof(uint32_t));
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
     //delete[] _data;
}


