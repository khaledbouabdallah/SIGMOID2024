#ifndef _SORTUTILS_H
#define _SORTUTILS_H

#include <vector>

class DataBase;
class DataPoint;

using namespace std;

int CompareByCatAndTS(const DataPoint& p1, const DataPoint& p2);
     
int CompareByTS(const DataPoint& p1, const DataPoint& p2);

void SwapIndices(int* indicesArray, int ind1, int ind2);

void SiftIndices(int* indices, const vector<DataPoint>& points, int i, int n, int (*funccomp)(const DataPoint&, const DataPoint&));
     
void SortIndices(int* indices, const vector<DataPoint>& points, int nPoints, int (*funccomp)(const DataPoint&, const DataPoint&));
     
int GetFirstPositionGETS(float ts, int* indices, const vector<DataPoint>& points, int start, int end);
     
int GetLastPositionLETS(float ts, int* indices, const vector<DataPoint>& points, int start, int end);



#endif
