#include <vector>
#include "../include/data.hpp"

using std::vector;

DataPoint::DataPoint(float timestamp, int c, float* data) {
    this->timestamp = timestamp;
    this->c = c;
    this->data = data;
}

float DataPoint::Get_timestamp() const {
    return this->timestamp;
}

int DataPoint::Get_c() const {
    return this->c;
}

float* DataPoint::Get_data() const {
    return this->data;
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

DataBase::DataBase(vector<DataPoint> data_points) {
    this->data_points = data_points;
}

DataBase::DataBase() {
    this->data_points = vector<DataPoint>();
}

vector<DataPoint> DataBase::Get_data_points() const {
    return this->data_points;
}

void DataBase::Set_data_points(vector<DataPoint> data_points) {
    this->data_points = data_points;
}

void DataBase::Add_data_point(DataPoint data_point) {
    this->data_points.push_back(data_point);
}
