#ifndef _INDEXSAXCLUSTERSRANGE_H
#define _INDEXSAXCLUSTERSRANGE_H

#include "globals.hpp"
#include <vector>
class DataBase;

using namespace std;

class SAXCluster {
public:
     SAXCode _code;
     int* _indicesByTS;
     int* _indicesByCatAndTS;
     int _countPoints;
};

class IndexSAXClustersRange {
private:
     vector<SAXCluster> clusters;
     
     const DataBase& _db; 
public:
     IndexSAXClustersRange(const DataBase& db);
     ~IndexSAXClustersRange();
     
     void BuildIndex();
private:
     int GetClusterIndice(const SAXCode& code);
     
  
};

#endif
