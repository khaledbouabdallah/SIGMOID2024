#ifndef _INDEXSAXCLUSTERSRANGE_H
#define _INDEXSAXCLUSTERSRANGE_H

#include "globals.hpp"
class DataBase;

struct SAXCluster {
     SAXCode _code;
     int* _indicesByTS;
     int* _indicesByCatAndTS;
     int* countPoints;
};

class IndexSAXClustersRange {
public:
     IndexSAXClustersRange(const DataBase& db);
     ~IndexSAXClustersRange();
     
     void BuildIndex();
     
private:
     SAXCluster* _clusters;
     int _nclusters;
     
     const DataBase& _db;   
};

#endif
