#include "QueryIVF.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"
#include "Utils.hpp"
#include <iostream>


// ============> No default constructor for QueryIVF ???
QueryIVF::QueryIVF(std::ifstream& ifs, const DataBase& db, const Kmeans& kmeans, int nprob) : Query(ifs,db){
        _kmeans = kmeans; // I need to store the kmeans object
        _nprob = nprob;
}

QueryIVF::~QueryIVF(){
}

void QueryIVF::run (int& switchquery){

    // find n cluster that are closest to the query
    // ==============> _data is the query point data ?? 
    std::vector<Cluster> clusters = _kmeans.getClusters(_data, _nprob);

    // for each cluster, find the closest point
    // =============> 
    for (int i = 0; i< clusters.size(); ++i) {
        Cluster& c = clusters[i];
        for (int j = 0; j< c.GetSize(); ++j) {
            const DataPoint& p = c.GetPoint(j);
            if (!IsValid(p)) continue;
            float dist = getDistance(p.GetData(), _data);
            
            _answer.CheckAndAdd(i,dist);
        }

    //  for (int i = 0; i< _db.GetSize(); ++i) {
    //       const DataPoint& p = _db.GetPoint(i);
    //       if (!IsValid(p)) continue;
    //       float dist = getDistance(p.GetData(), _data);
          
    //       _answer.CheckAndAdd(i,dist);
    //  } 

     _isFinished = 1;
}