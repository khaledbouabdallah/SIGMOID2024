#include "DataPoint.hpp"
#include "globals.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

DataPoint::DataPoint(ifstream& ifs){
     _data = new float[DATA_SIZE];
     float cfloat;
     ifs.read((char *)&cfloat, sizeof(uint32_t)); //categories are stored as floats !!!
     _c = int(cfloat);
     ifs.read((char *)&_timestamp, sizeof(uint32_t));
     ifs.read((char *)_data, DATA_SIZE * sizeof(uint32_t));
}

DataPoint::DataPoint(const DataPoint& other) {
     _data = new float[DATA_SIZE];
     memcpy(_data, other._data, DATA_SIZE*sizeof(float));
     _c = other._c;
     _timestamp = other._timestamp;
     std::bitset<nombres_de_bits >* sax = malloc(sizeof((std::bitset<nombres_de_bits >)nombres_de_bits);
}
     
float DataPoint::GetTS() const {
     return _timestamp;
}

std::bitset<nombres_de_bits >* DataPoint::Getsax() const {
     return sax;
}

void DataPoint::Setsax(std::bitset<nombres_de_bits >* Sax) const {
     sax = Sax;
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


