#include "Utils.hpp"
#include "globals.hpp"
#include <cmath>
#include <iostream>

using namespace std;


// needed for PAA
float calculateMean(float* data, int size) {
     float sum = 0.0;
     for (int i = 0; i < size; i++) {
          sum += data[i];
     }
     return sum / size;
}

float getDistance(float* data1, float* data2) {
     float sum = 0;
     for (int i = 0; i < DATA_SIZE; i++) 
          sum += ((data1[i] - data2[i])*(data1[i] - data2[i]));
     
     return sqrt(sum);
}

float* getBreakPoints(int numSegments) {
    switch (numSegments)
    {
    case 2:
        return (float*)BREAK_POINTS_2;
    case 3:
        return (float*)BREAK_POINTS_3;
    case 8:
        return (float*)BREAK_POINTS_8;
    case 16:
        return (float*)BREAK_POINTS_16;
    case 32:
        return (float*)BREAK_POINTS_32;
    case 64:
        return (float*)BREAK_POINTS_64;
    case 128:
        return (float*)BREAK_POINTS_128;
    case 256:
        return (float*)BREAK_POINTS_256;
    case 512:
        return (float*)BREAK_POINTS_512;
    default:
        return (float*)BREAK_POINTS_256;
    }
}
