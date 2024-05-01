#include "QueryIVF.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"
#include "Utils.hpp"
#include <iostream>


// ============> 
// QueryIVF::QueryIVF(std::ifstream& ifs, const DataBase& db,  Kmeans& kmeans, int nprob) : Query(ifs,db), _kmeans(kmeans), _nprob(nprob){

// }

// QueryIVF::~QueryIVF(){
// }

// void QueryIVF::run (int& switchquery){

//     // find n cluster that are closest to the query
//     std::vector<Cluster> clusters = _kmeans.getClusters(_data, _nprob);

//     // for each cluster, find the closest point
//     // =============> 
//     for (int i = 0; i< clusters.size(); ++i) {
//         Cluster& c = clusters[i];
//         for (int j = 0; j< c.GetSize(); ++j) {
//             const DataPoint& p = c.GetPoint(j);
//             if (!IsValid(p)) continue;
//             float dist = getDistance(p.GetData(), _data);
            
//             _answer.CheckAndAdd(i,dist);
//         }

//      _isFinished = 1;
// }
// }