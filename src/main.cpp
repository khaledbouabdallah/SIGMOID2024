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
#include <chrono>
#include <cstdint>
#include "IndexSAXTrie.hpp"
#include "QuerySAXLookaround.hpp"
#include "Kmeans.hpp"
#include "QueryIVF.hpp"

using namespace std;

#define RECALL

void readIndices(ifstream &ifs, vector<int> &indices)
{
     for (int i = 0; i < DATA_SIZE; ++i)
     {
          int k;
          ifs.read((char *)&k, sizeof(uint32_t));
          indices.push_back(k);
     }
}

int allDistinct(vector<int> &vec)
{
     set<int> ss;
     for (int val : vec)
          ss.insert(val);
     if (ss.size() != DATA_SIZE)
          return 0;
     return 1;
}

float GetRecall(DataBase &db, QuerySet &qset, const char *filecheck, const char *fileref)
{
     ifstream ifscheck;
     ifscheck.open(filecheck, std::ios::binary);
     assert(ifscheck.is_open());

     ifstream ifsref;
     ifsref.open(fileref, std::ios::binary);
     assert(ifsref.is_open());

     Query **queries = qset.GetQueries();
     int nq = qset.GetQueryCount();

     float rec = 0;

     for (int i = 0; i < nq; ++i)
     {
          // cout<<i<<endl;
          int countgood = 0;

          vector<int> indicescheck;
          readIndices(ifscheck, indicescheck);
          vector<int> indicesref;
          readIndices(ifsref, indicesref);

          if (!allDistinct(indicesref))
               cout << "ref not distinct" << endl;

          float maxdistref = -1;
          for (int ind : indicesref)
          {
               const DataPoint &p = db.GetPoint(ind);
               float crtdist = getDistance(queries[i]->GetData(), p.GetData());
               if (crtdist > maxdistref)
                    maxdistref = crtdist;
          }

          for (int ind : indicescheck)
          {
               // cout<<ind<<endl;
               const DataPoint &p = db.GetPoint(ind);
               float crtdist = getDistance(queries[i]->GetData(), p.GetData());
               if (crtdist <= maxdistref)
                    countgood++;
          }
          // cout<<"here"<<endl;
          rec += (float)countgood / (float)DATA_SIZE;
     }
     rec /= nq;
     ifscheck.close();
     ifsref.close();

     return rec;
}

volatile int done = 0;

void timesup(int sig)
{
     done = 1;
}

int main()
{
     vector<int> k_values = {1, 10, 50, 100, 256, 512, 1024, 10000};
     vector<int> nprob_values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
     //const char* pointsInput = "data/dummy-data.bin";
     //const char* pointsInput = "../data/dummy-data.bin";
     const char *pointsInput = "data/contest-data-release-1m.bin";
     // const char* pointsInput = "../data/contest-data-release-10m.bin";

     //const char* queriesInput = "data/dummy-queries.bin";
     //const char* queriesInput = "../data/dummy-queries.bin";
     const char *queriesInput = "data/contest-queries-release-1m.bin";
     // const char* queriesInput = "../data/Public-4M-queries.bin";

     int runType = 1;   // 0 = normal, 1 = multi-thread
     int queryType = 7; // 0 = seq scan, 1 = seq scan range, 2 = seq scan incremental, 3 = seq scan range incremental, 4 = sax filter range, 5 = sax filter only
     // 6 = range SAX lookaround

     const char *ansoutput = "output.bin";
     // const char* ansoutput = "../data/dummy-output-current.bin";
     // const char* ansoutput = "../data/relsmall-output-current.bin";
     // const char* ansoutput = ".../data/relbig-output-current.bin";

     //const char* true_path = "data/dummy-output-reference.bin";
     const char *true_path = "data/rellsmall-output-reference.bin";
     for (int k : k_values)
     {
          for (int nprob : nprob_values)
          {
               if (nprob > k)
                    continue;
               auto start = std::chrono::high_resolution_clock::now();
               //cout << "Reading points with k = " << k << " and nprob = " << nprob << endl;
               done = 0;
               signal(SIGALRM, timesup);
               alarm(TIMETORUN);

               //cout << "reading points" << endl;
               DataBase db = DataBase(pointsInput);
               // cout << "sorting by cat and ts" << endl;
               // db.SortByCatAndTS();
               // cout << "processing categories" << endl;
               // db.ProcessCategories();
               // cout << "sorting by ts" << endl;
               // db.SortByTS();
               //  cout<<"computing sax stuff"<<endl;
               //  db.ComputeSAXStuff();

               //cout << "running kmeans" << endl;
               Kmeans kmeans = Kmeans(k); // k 1024
               kmeans.set_max_iteration(30);
               kmeans.set_min_delta(0.1);
               kmeans.set_random_seed(1);
               kmeans.set_verbose_level(0);          // 0 = no output, 1 = some output, 2 = all output
               kmeans.fit(db.GetPoints(), "random"); // "kmeans++" or "random

               //cout << "sorting clusters data" << endl;
               for (int i = 0; i < kmeans.get_k(); ++i)
                    kmeans.getCluster(i)->MakeAndSortIndices(db);

               //cout << "reading queries" << endl;
               QuerySet qset = QuerySet(queriesInput, db, queryType);
               if (queryType == 7)
               {
                    int qcount = qset.GetQueryCount();
                    Query **queries = qset.GetQueries();
                    for (int i = 0; i < qcount; ++i)
                    {
                         ((QueryIVF *)queries[i])->setKmeans(&kmeans);
                         ((QueryIVF *)queries[i])->setNProb(nprob);
                    }
               }

               Query **queries = qset.GetQueries();
               int nq = qset.GetQueryCount();

               if (runType == 0)
               {
                    int dummyswitch;
                    for (int i = 0; i < nq && !done; ++i)
                    {
                         // cout<<"running query "<<i<<endl;
                         // if (queryType== 5) ((QuerySAXTrie*)queries[i])->SetIndex(&index);
                         queries[i]->run(dummyswitch);
                    }
                    qset.WriteOutput(ansoutput);
               }
               else
               {
                    QueryRunManager runManager(queries, qset._queryIndices, nq, NTHREADS, 0, 1); // no incr, assign with query vector queue
                    runManager.run();
                    qset.WriteOutput(ansoutput);
               }

#ifdef RECALL
               float rec = GetRecall(db, qset, "output.bin", true_path);
               
#endif
          auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
          cout<<"============================"<<endl;
          cout << "recall: " << rec << endl;
          cout<<"Time taken with k = " << k << " and nprob = " << nprob << endl;
          cout << "Time taken: " << duration.count() /1000000<< " s" << endl;
          cout<<"============================"<<endl;
          //delete output file
          //remove(ansoutput);
          }
     }
     return 0;
}

