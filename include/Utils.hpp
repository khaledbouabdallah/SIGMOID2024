#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <vector>

float calculateMean(float* data, int size);

float calculateMean(float* data, int start, int end);

float getDistance(float* data1, float* data2);

std::vector<float> getBreakPoints(int numSegments);


#endif
