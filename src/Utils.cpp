#include "Utils.hpp"
#include "globals.hpp"
#include <cmath>


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
