#include "Utils.hpp"
#include "globals.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


// used for Normalization
float calculateMean(float* data, int size) {
     float sum = 0.0;
     for (int i = 0; i < size; i++) {
          sum += data[i];
     }
     return sum / size;
}

// used for Normalization
float calculateStd(float* data, int size, float mean) {
     float sum = 0.0;
     for (int i = 0; i < size; i++) {
          sum += (data[i] - mean)*(data[i] - mean);
     }
     return sqrt(sum / size);
}

// used for PAA
float calculateMean(float* data, int start, int end) {
     float sum = 0.0;
     for (int i = start; i <= end; i++) {
          sum += data[i];
     }
     return sum / (end-start+1);
}

float getDistance(float* data1, float* data2) {
     float sum = 0;
     for (int i = 0; i < DATA_SIZE; i++) 
          sum += ((data1[i] - data2[i])*(data1[i] - data2[i]));
     return sqrt(sum);
}

float getPaaDistance(float* data1, float* data2) {
     float sum = 0;
     for (int i = 0; i < PAA_SEGMENTS; i++) 
          sum += ((data1[i] - data2[i])*(data1[i] - data2[i]));
     return sqrt(sum);
}

float getSAXDistance(uint64_t* sax1, uint64_t* sax2, const vector<float>& breakpoints){
    
     float sumdist = 0;
     for (int i = 0; i < PAA_SEGMENTS; ++i) {
          
          int max = sax1[i];
          
          if (sax2[i] > max) max = sax2[i];
          int min = sax1[i]+sax2[i]-max;
        
          float dist = 0;
          
          
          if (max-min >1) { 
               dist = breakpoints[max-1]-breakpoints[min];
               dist = dist*dist;
          }
          sumdist+=dist;
     }
     return sqrt(sumdist);
}

std::vector<float> getBreakPoints(int numSegments, float mean, float stddev) {
    std::vector<float> bp;
    switch (numSegments)
    {
    case 2:
        bp = BREAK_POINTS_2; break;
    case 3:
        bp =   BREAK_POINTS_3; break;
    case 8:
        bp =   BREAK_POINTS_8;break;
    case 16:
        bp =   BREAK_POINTS_16;break;
    case 32:
        bp =   BREAK_POINTS_32;break;
    case 64:
        bp =   BREAK_POINTS_64;break;
    case 128:
        bp =   BREAK_POINTS_128;break;
    case 256:
        bp =   BREAK_POINTS_256;break;
    case 512:
        bp =   BREAK_POINTS_512;break;
    default:
        bp =   BREAK_POINTS_256;break;
    }
    
    //apply transform
    //cout<<stddev<<" "<<mean<<endl;
    //for (int i = 0; i<bp.size(); ++i) {
    //      bp[i] = bp[i]*stddev+mean;
          //cout<<bp[i]<<endl;
    //}
    return bp;
}
