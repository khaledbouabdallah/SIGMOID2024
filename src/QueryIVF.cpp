#include "../include/QueryIVF.hpp"
#include "../include/DataPoint.hpp"
#include "../include/DataBase.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <Kmeans.hpp>

QueryIVF::QueryIVF(std::ifstream& ifs, const DataBase& db) : Query(ifs,db) {

}


QueryIVF::~QueryIVF(){
}

void QueryIVF::run (int& switchquery){

    // find n cluster that are closest to the query
    std::vector<Cluster*> clusters = _kmeans->getClusters(_data, _nprob);

    // for each cluster, find the closest point
    // =============> 
    for (int i = 0; i< clusters.size(); ++i) {
        Cluster& c = *clusters[i];
        for (int j = 0; j< c.GetSize(); ++j) {
            const DataPoint& p = _db.GetPoint(c.getPoint(j));
            if (!IsValid(p)) continue;
            float dist = getDistance(p.GetData(), _data);
            
            _answer.CheckAndAdd(i,dist);
        }

     _isFinished = 1;
}
}