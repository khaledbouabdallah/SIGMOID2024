#include "Utils.hpp"

void swapIndices(int* indicesArray, int ind1, int ind2) {
     int aux = indicesArray[ind1]; 
     indicesArray[ind1] = indicesArray[ind2];
     indicesArray[ind2] = aux;
}

// needed for PAA
float calculateMean(float* data, int size) {
     float sum = 0.0;
     for (int i = 0; i < size; i++) {
          sum += data[i];
     }
     return sum / size;
}