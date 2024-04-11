#include "Utils.hpp"
#include "globals.hpp"
#include <cmath>

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

float distance(float* data1, float* data2) {
     float sum = 0;
     for (int i = 0; i < DATA_SIZE; i++) 
          sum += data1[i] * data2[i];
     return sqrt(sum);
}
