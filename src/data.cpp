#include "../include/data.hpp"
#include <fstream>


int add(int a, int b) {
    return a + b;
}


DataPoint::DataPoint(float timestamp, int c, float* data) {
    this->timestamp = timestamp;
    this->c = c;
    this->data = data;
}

float DataPoint::Get_timestamp() const {
    return timestamp;
}

int DataPoint::Get_c() const {
    return c;
}

float* DataPoint::Get_data() const {
    return data;
}

void DataPoint::Set_timestamp(float timestamp) {
    this->timestamp = timestamp;
}

void DataPoint::Set_c(int c) {
    this->c = c;
}

void DataPoint::Set_data(float* data) {
    this->data = data;
}

DataBase::DataBase(std::vector<DataPoint> data_points) {
    this->data_points = data_points;
}

std::vector<DataPoint> DataBase::Get_data_points() const {
    return data_points;
}

void DataBase::Set_data_points(std::vector<DataPoint> data_points) {
    this->data_points = data_points;
}

void DataBase::Add_data_point(DataPoint data_point) {
    data_points.push_back(data_point);
}

DataPoint DataBase::Get_data_point(int index) {
    return data_points[index];
}

int DataBase::Get_size() {
    return data_points.size();
}

void DataBase::Read_data_from_file(const char* filename) {
  
}

DataBase::~DataBase() {
    // Destructor implementation

}
