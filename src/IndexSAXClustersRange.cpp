#include "IndexSAXClustersRange.hpp"
#include "DataBase.hpp"
#include "DataPoint.hpp"

IndexSAXClustersRange::IndexSAXClustersRange(const DataBase& db): _db(db) {   
}

IndexSAXClustersRange::~IndexSAXClustersRange(){
}

void IndexSAXClustersRange::BuildIndex() {
//TODO
     int nPoints = _db.GetSize();
     
     //first count points within each cluster 
     for (int i = 0; i < nPoints; ++i) {
          const DataPoint& p = _db.GetPoint(i);
          int code = 0 ; //p.GetSAX();
          int clusterind = GetClusterIndice(code);
          clusters[clusterind]._countPoints++;
     }
     
     //then allocate and reset
     for (SAXCluster cluster:clusters) {
          cluster._indicesByTS = new int[cluster._countPoints];
          cluster._indicesByCatAndTS = new int[cluster._countPoints];
          cluster._countPoints = 0;
     }
     
     //now fill with indices
     for (int i = 0; i < nPoints; ++i) {
          const DataPoint& p = _db.GetPoint(i);
          int code = 0 ; //p.GetSAX();
          int clusterind = GetClusterIndice(code);
          clusters[clusterind]. _indicesByTS[clusters[clusterind]._countPoints] = i;
          clusters[clusterind]. _indicesByCatAndTS[clusters[clusterind]._countPoints] = i;
          clusters[clusterind]._countPoints++;
     }
     
     //now sort             
}

int IndexSAXClustersRange::GetClusterIndice(const SAXCode& code){
//TODO
     int clusterInd = -1;
     if (clusterInd == -1) {
          SAXCluster cluster;
          cluster._code = code;
          cluster._countPoints = 0;
          cluster._indicesByTS = cluster._indicesByCatAndTS = NULL;
          clusters.push_back(cluster);
          return clusters.size();
     }
     else 
          return clusterInd;
}
