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
    int count = 0;
    int count_c = 0;
    for (int i = 0; i< clusters.size(); ++i) {
        Cluster& c = *clusters[i];
        count_c += c.GetSize();
        
        /*
        for (int j = 0; j< c.GetSize(); ++j) {
            const DataPoint& p = _db.GetPoint(c.getPoint(j));
            count ++;
            if (!IsValid(p)) continue;
            float dist = getDistance(p.GetData(), _data);
            _answer.CheckAndAdd(c.getPoint(j),dist);
        } 
        */
        
        int* indices;
        int start, end;
        c.getSearchRange(_db, _c, _tsl, _tsr, indices, start, end);
        if (start == -1) continue; //no answers in this cluster
        //cout<<start<<" "<<end<<" "<<c.GetSize()<<endl;
        
        if (start<0 || start>end || end>c.GetSize()){
          //cout<<"big error "<<_c<<" "<<_tsl<<" "<<_tsr<<endl;
          
        }
        
        for (int j = start; j<end; ++j) {
            const DataPoint& p = _db.GetPoint(indices[j]);
            count ++;
            float dist = getDistance(p.GetData(), _data);
            _answer.CheckAndAdd(indices[j],dist);
        } 
            
    }

_isFinished = 1;
}
