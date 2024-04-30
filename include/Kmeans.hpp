#ifndef _KMEANS_H
#define _KMEANS_H


#include <vector>
#include "globals.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"


class Cluster: public DataBase {

    private:
        std::vector<DataPoint> _points;
        DataPoint _centroid;
        int _id;
        int _countPoints;
        int* _categories;
        // ?? =>
        int* _catstart;
        int* _catend;
        // timestamp begin and end ??

};



class Kmeans
{
private:

    int _k;
    std::vector<Cluster> _clusters;
    int _maxIter;
    float _tolerance;


public:

    inline Kmeans(int k, int maxIter, float tolerance) : _k(k), _maxIter(maxIter), _tolerance(tolerance) {}
    void fit(std::vector<DataPoint>& data);
    std::vector<Cluster> getClusters(float* point, int nprob);
    ~Kmeans();

};

#endif