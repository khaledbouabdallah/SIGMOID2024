#include "IndexSAXClustersRange.hpp"
#include "DataBase.hpp"

IndexSAXClustersRange::IndexSAXClustersRange(const DataBase& db): _db(db), _clusters(NULL), _nclusters(0) {   
}

IndexSAXClustersRange::~IndexSAXClustersRange(){
}

void IndexSAXClustersRange::BuildIndex() {
     int nPoints = _db.GetSize();
}
