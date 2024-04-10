#include "Utils.hpp"

void swapIndices(int* indicesArray, int ind1, int ind2) {
     int aux = indicesArray[ind1]; 
     indicesArray[ind1] = indicesArray[ind2];
     indicesArray[ind2] = aux;
}
