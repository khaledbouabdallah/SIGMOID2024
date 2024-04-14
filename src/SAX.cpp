#include <vector>
#include "SAX.hpp"
#include "globals.hpp"
#include "Utils.hpp"

using std::vector;

SAX::SAX(int wordSize,int alphaSize) {
    _wordSize = wordSize;
    _alphaSize = alphaSize;
    _breakpoints = getBreakPoints(alphaSize);

}


float* SAX::ToPAA(float* vector) {
     return NULL;
}

int SAX::ToSAX(float* paa) {
     return 0;
}
     
int* SAX::ToSAX(float* vector, DataBase& db) {
     return NULL;
}

SAX::~SAX() {

}

int* SAX::splitsX(int wordSize) {
     return NULL;
}
