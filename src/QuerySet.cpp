#include "QuerySet.hpp"
#include <fstream>
#include "assert.h"
#include "Query.hpp"

using namespace std;

QuerySet::QuerySet(const char* filename) {     
     ifstream ifs;
     ifs.open(filename, std::ios::binary);
     assert(ifs.is_open());
     
     ifs.read((char *)&_queryCount, sizeof(uint32_t));
     _queries = new Query*[_queryCount];
     for (int i = 0; i < _queryCount; ++i)
          _queries[i] = new Query(ifs);
}

int QuerySet::GetQueryCount(){
     return _queryCount;
}

QuerySet::~QuerySet(){
     for (int i = 0; i < _queryCount; ++i)
          delete _queries[i];
     delete[] _queries;
}
     
