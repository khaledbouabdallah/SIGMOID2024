#include "../include/QuerySet.hpp"
#include <fstream>
#include <iostream>
#include "assert.h"
#include "../include/Query.hpp"
#include "../include/QuerySeqScan.hpp"
#include "../include/QuerySeqScanRange.hpp"
#include "../include/QuerySeqScanIncremental.hpp"
#include "../include/QuerySeqScanRangeIncremental.hpp"
#include "../include/QueryRangeSAXFilter.hpp"
#include "../include/QueryRangeSAXOnly.hpp"
#include "../include/QuerySAXLookaround.hpp"
#include "../include/SAX.hpp"
#include "../include/SortUtils.hpp"
#include "../include/Utils.hpp"
#include "../include/globals.hpp"

using namespace std;

QuerySet::QuerySet(const char* filename, const DataBase& db, int queryType): _db(db), _queryCount(0) { 
   
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
               case 5: _queries[i] = new QueryRangeSAXOnly(ifs, db); break;
               case 6: _queries[i] = new QuerySAXLookaround(ifs, db); break;
          }
     }
     
     _queryIndices = new int[_queryCount];
     for (int i = 0; i < _queryCount; ++i)
          _queryIndices[i] = i;
     SortIndices(_queryIndices, _queries, _queryCount, CompareBySelectivity);
}

void QuerySet::ComputeSAXStuff(){
     //create SAX maker with normalized breakpoints
     SAX saxmaker(PAA_SEGMENTS, SAX_CARD, _db.GetGlobalMean(), _db.GetGlobalStd());
  
     for (int i = 0; i < _queryCount; ++i) {
          //float* paa = saxmaker.ToPAA(_queries[i]->GetData(), DATA_SIZE);
          //_queries[i]->SetPaa(paa);
          uint64_t* sax = saxmaker.ToSAX(_queries[i]->GetData(), DATA_SIZE); //this is whole sax, no paa
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


     
