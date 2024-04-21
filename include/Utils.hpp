#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <vector>
#include <cstdint>


float calculateMean(float* data, int size);

float calculateMean(float* data, int start, int end);

float getDistance(float* data1, float* data2);

std::vector<float> getBreakPoints(int numSegments, float mean, float stddev);

float getSAXDistance(uint64_t* sax1, uint64_t* sax2, const std::vector<float>& breakpoints);

#endif
