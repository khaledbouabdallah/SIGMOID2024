#include <vector>
#include "SAX.hpp"
#include "globals.hpp"
using std::vector;

SAX::SAX(int wordSize,int alphaSize) {
    _wordSize = wordSize;
    _alphaSize = alphaSize;
    _breakpoints = getBreakPoints(alphaSize);

}


float* SAX::ToPAA(float* vector) {

}

int SAX::ToSAX(float* paa) {

}
     
int* SAX::ToSAX(float* vector, DataBase& db) {

}

SAX::~SAX() {

}

int* SAX::splitsX(int wordSize) {

}