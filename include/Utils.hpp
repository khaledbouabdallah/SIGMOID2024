#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <vector>
#include <cstdint>


float calculateMean(float* data, int size);

float calculateMean(float* data, int start, int end);

float calculateStd(float* data, int size, float mean);

float getDistance(float* data1, float* data2);

float getPaaDistance(float* data1, float* data2);

void normalizeData(float* data, int size, float mean, float stdev);

std::vector<float> getBreakPoints(int numSegments, float mean, float stddev);

#endif
