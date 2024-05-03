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

    

    // // change nprob on class of query switch case
    // // TODO: switch case for nprob 

    switch (_type)
    {
    case 0: _nprob = 14;
        break;
    case 1: _nprob = 21;
        break;
    case 2: _nprob = 21;
        break;
    case 3: _nprob = 24;
        break;
    default:
        break;
    }

    //find n cluster that are closest to the query
    std::vector<Cluster*> clusters = _kmeans->getClusters(_data, _nprob);
    
    
    // for each cluster, find the closest point
    // =============> 

    for (int i = 0; i< clusters.size(); ++i) {

        Cluster& c = *clusters[i];



        // Todo: check if the cluster is valid
        // if not, continue


        // Todo: Range search in the cluster
        

        for (int j = 0; j< c.GetSize(); ++j) {
            const DataPoint& p = _db.GetPoint(c.getPoint(j));
            //const DataPoint& p = c._datapoints[j];
            if (!IsValid(p)) continue;
            float dist = getDistance(p.GetData(), _data);
            _answer.CheckAndAdd(c.getPoint(j),dist);
        }    
    }

_isFinished = 1;
}
