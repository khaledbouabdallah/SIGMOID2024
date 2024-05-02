#include "../include/Utils.hpp"
#include "../include/globals.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

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
     //return sqrt(sum);
     return sum;
}

float getPaaDistance(float* data1, float* data2) {
     float sum = 0;
     for (int i = 0; i < PAA_SEGMENTS; i++) 
          sum += ((data1[i] - data2[i])*(data1[i] - data2[i]));
     //return sqrt(sum);
     return sum;
}

void normalizeData(float* data, int size, float mean, float stdev){
      for (int j = 0; j<size; ++j) {
          data[j] = (data[j] - mean)/stdev;
      }
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
    for (int i = 0; i<bp.size(); ++i) {
          bp[i] = bp[i]*stddev+mean;
          //cout<<bp[i]<<endl;
    }
    return bp;
}


// Function to return indices of the k minimum elements in a float array
std::vector<int> findKMinIndices(const std::vector<float>& arr, int k) {
    // Create a vector of pairs (value, index) to maintain the original indices
    std::vector<std::pair<float, int>> indexedArray;
    indexedArray.reserve(arr.size());

    // Fill the indexed array with (value, index) pairs
    for (int i = 0; i < arr.size(); ++i) {
        indexedArray.push_back({arr[i], i});
    }

    std::cout << "unSorted array: " << std::endl;
     for (int i = 0; i < indexedArray.size(); ++i) {
         std::cout << indexedArray[i].first << " " << indexedArray[i].second << std::endl;
     }

    // Sort the indexed array based on the values
    std::sort(indexedArray.begin(), indexedArray.end(), [](const auto& a, const auto& b) {
        return a.first < b.first; // sort by value in ascending order
    });

    // print the sorted array
    std::cout << "Sorted array: " << std::endl;
     for (int i = 0; i < indexedArray.size(); ++i) {
         std::cout << indexedArray[i].first << " " << indexedArray[i].second << std::endl;
     }

    // Extract the indices of the k smallest elements
    std::vector<int> minIndices;
    minIndices.reserve(k);

    for (int i = 0; i < k; ++i) {
        minIndices.push_back(indexedArray[i].second);
    }

    

    return minIndices;
}

bool inVector(const std::vector<int>& vec, int index) {
    return std::find(vec.begin(), vec.end(), index) != vec.end();
}