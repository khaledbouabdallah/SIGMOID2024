#include <vector>
#include "SAX.hpp"
using std::vector;

SAX::SAX(int wordSize,int alphaSize, float* breakpoints) {
    _wordSize = wordSize;
    _alphaSize = alphaSize;
    _breakpoints = breakpoints;

}

float* SAX::PAA(float* vector, int size) {


}

float* SAX::getBreakpoints(int cardinality) {

}

SAX::~SAX() {
}
