#ifndef _QUERYIVF_H
#define _QUERYIVF_H

#include "Query.hpp"
#include "Kmeans.hpp"

class QueryIVF: public Query {
     
private:
     Kmeans* _kmeans;
     int _nprob;

public:

     QueryIVF(std::ifstream& ifs, const DataBase& db);
    
     ~QueryIVF();
     
     virtual void run (int& switchquery); 

     void inline setNProb(int nprob) {_nprob = nprob;}

     int inline getNProb() const {return _nprob;}

     Kmeans*  getKmeans() {return _kmeans;}

     void inline setKmeans(Kmeans* kmeans) {_kmeans = kmeans;}

};


#endif
