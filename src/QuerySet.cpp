#include "QuerySet.hpp"
#include <fstream>
#include <iostream>
#include "assert.h"
#include "Query.hpp"
#include "QuerySeqScan.hpp"

using namespace std;

QuerySet::QuerySet(const char* filename, const DataBase& db): _db(db) {     
     ifstream ifs;
     ifs.open(filename, std::ios::binary);
     assert(ifs.is_open());
     
     ifs.read((char *)&_queryCount, sizeof(uint32_t));
     _queries = new Query*[_queryCount];
     for (int i = 0; i < _queryCount; ++i) {
          //cout<<"query "<<i<<endl;
          _queries[i] = new QuerySeqScan(ifs, db);
     }
          
}

int QuerySet::GetQueryCount(){
     return _queryCount;
}

QuerySet::~QuerySet(){
     for (int i = 0; i < _queryCount; ++i)
          delete _queries[i];
     delete[] _queries;
}

void QuerySet::WriteOutput(const char* filename){
     std::ofstream ofs(filename, std::ios::out | std::ios::binary);
     for (int i = 0; i < _queryCount; ++i)
          _queries[i]->WriteOutput(ofs);
     ofs.close();
}
     
