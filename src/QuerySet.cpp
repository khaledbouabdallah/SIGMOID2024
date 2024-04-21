#include "QuerySet.hpp"
#include <fstream>
#include <iostream>
#include "assert.h"
#include "Query.hpp"
#include "QuerySeqScan.hpp"
#include "QuerySeqScanRange.hpp"
#include "QuerySeqScanIncremental.hpp"
#include "QuerySeqScanRangeIncremental.hpp"
#include "QueryRangeSAXFilter.hpp"
#include "SAX.hpp"

using namespace std;

QuerySet::QuerySet(const char* filename, const DataBase& db, int queryType): _db(db), _queryCount(0) { 
     SAX saxmaker(PAA_SEGMENTS, SAX_CARD, _db.GetGlobalMean(), _db.GetGlobalStd());
  
     ifstream ifs;
     ifs.open(filename, std::ios::binary);
     assert(ifs.is_open());

     
     ifs.read((char *)&_queryCount, sizeof(uint32_t));

     _queries = new Query*[_queryCount];
     for (int i = 0; i < _queryCount; ++i) {
          switch (queryType){
               case 0: _queries[i] = new QuerySeqScan(ifs, db); break;
               case 1: _queries[i] = new QuerySeqScanRange(ifs, db); break;
               case 2: _queries[i] = new QuerySeqScanIncremental(ifs, db); break;
               case 3: _queries[i] = new QuerySeqScanRangeIncremental(ifs, db); break;
               case 4: _queries[i] = new QueryRangeSAXFilter(ifs, db); break;
          }
          float* paa = saxmaker.ToPAA(_queries[i]->GetData(), DATA_SIZE);
          _queries[i]->SetPaa(paa);
          uint64_t* sax = saxmaker.ToSAX(paa,PAA_SEGMENTS);
          _queries[i]->SetSAX(sax);
     }
          
}

int QuerySet::GetQueryCount(){
     return _queryCount;
}

Query** QuerySet::GetQueries() const {
     return _queries;
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
     
