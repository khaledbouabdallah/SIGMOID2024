#include "DataBase.hpp"
#include "QuerySet.hpp"
#include "Query.hpp"
#include "globals.hpp"
#include "Utils.hpp"
#include <signal.h>
#include <iostream>
#include <fstream>
#include "QueryRunManager.hpp"
#include "DataBase.hpp"
#include "QuerySeqScanIncremental.hpp"
#include "QuerySeqScanRangeIncremental.hpp"
#include <vector>
#include <set>
#include "assert.h"
#include <cstdint>

using namespace std;

#define RECALL

void readIndices(ifstream& ifs, vector<int>&indices){    
     for (int i = 0; i < DATA_SIZE; ++i){
          int k;
          ifs.read((char *)&k, sizeof(uint32_t));
          indices.push_back(k);
     }   
}

int allDistinct(vector<int>& vec){
     set<int> ss;
     for (int val:vec)
          ss.insert(val);
     if (ss.size()!=DATA_SIZE) return 0;
     return 1;
}

float GetRecall(DataBase& db, QuerySet& qset, const char* filecheck, const char* fileref) {
     ifstream ifscheck;
     ifscheck.open(filecheck, std::ios::binary);
     assert(ifscheck.is_open());
     
     ifstream ifsref;
     ifsref.open(fileref, std::ios::binary);
     assert(ifsref.is_open());
     
     Query** queries = qset.GetQueries();
     int nq = qset.GetQueryCount();
     
     float rec= 0;
     
     for (int i = 0; i<nq; ++i) {
          int countgood = 0;
          
          vector<int>indicescheck;
          readIndices(ifscheck, indicescheck);
          vector<int>indicesref;
          readIndices(ifsref, indicesref);
          
          if (!allDistinct(indicesref))
               cout<<"ref not distinct"<<endl;
           
          float maxdistref = -1;
          for (int ind: indicesref) {
               const DataPoint& p = db.GetPoint(ind);
               float crtdist = getDistance(queries[i]->GetData(), p.GetData());
               if (crtdist> maxdistref)
                    maxdistref = crtdist;
          }
          //cout<<maxdistref<<endl;
          
          for (int ind: indicescheck) {
               const DataPoint& p = db.GetPoint(ind);
               float crtdist = getDistance(queries[i]->GetData(), p.GetData());
               if (crtdist<= maxdistref)
                    countgood ++;
          }
          rec+=(float)countgood/(float)DATA_SIZE;
      }
      rec/=nq;
      ifscheck.close();
      ifsref.close();
          
          
      return rec;
   
}


volatile int done = 0;

void timesup (int sig){
     done = 1;
}


int main() {
     //const char* pointsInput = "../data/dummy-data.bin";
     const char* pointsInput = "../data/contest-data-release-1m.bin";
     //const char* pointsInput = "../data/contest-data-release-10m.bin";
     
     //const char* queriesInput = "../data/dummy-queries.bin";
     const char* queriesInput = "../data/contest-queries-release-1m.bin";
     //const char* queriesInput = "../data/Public-4M-queries.bin";
     
     int runType = 1; //0 = normal, 1 = multi-thread
     int queryType = 0; //0 = seq scan, 1 = seq scan range, 2 = seq scan incremental, 3 = seq scan range incremental, 4 = sax filter range
     
     //const char* ansoutput = "../data/dummy-output-current.bin";
     const char* ansoutput = "../data/relsmall-output-current.bin";
     //const char* ansoutput = "../data/relsmall-range-mt.bin";
     
     
     done = 0;
     signal( SIGALRM, timesup);
     alarm(TIMETORUN);
     
     cout<<"reading points"<<endl;
     DataBase db = DataBase(pointsInput);
     cout<<"sorting by cat and ts"<<endl;
     db.SortByCatAndTS();
     cout<<"processing categories"<<endl;
     db.ProcessCategories();
     cout<<"sorting by ts"<<endl;
     db.SortByTS();
     
     cout<<"reading queries"<<endl;
     QuerySet qset = QuerySet(queriesInput, db, queryType);

#ifndef RECALL
     Query** queries = qset.GetQueries();
     int nq = qset.GetQueryCount();
     
     if (runType == 0) {
          int dummyswitch;
          for (int i = 0; i<nq; ++i) {
               cout<<"running query "<<i<<endl;
               queries[i]->run(dummyswitch);
          }
          qset.WriteOutput(ansoutput);       
     } else {
          QueryRunManager runManager (queries, nq, NTHREADS, 0, 1); //no incr, assign with vector queue
          runManager.run();
          qset.WriteOutput(ansoutput);   
     }
#else
     float rec = GetRecall(db, qset, "../data/relsmall-output-current.bin", "../data/rellsmall-output-reference.bin");
     cout<<rec<<endl;
#endif
     
     return 0;
}



 /*        
          for (int i = 0; i<nq; ++i) 
               if (!queries[i]-> IsFinished()){
                    cout<< "QUERY "<<i<<" ";
                    if (queryType == 2)
                         ((QuerySeqScanIncremental*)queries[i])->PrintDelta();
                    else
                         ((QuerySeqScanRangeIncremental*)queries[i])->PrintDelta();
               }
*/
   
