#include "DataBase.hpp"
#include "QuerySet.hpp"
#include "Query.hpp"
#include "globals.hpp"
#include <signal.h>
#include <iostream>
#include <fstream>
#include "QueryRunManager.hpp"

using namespace std;

volatile int done = 0;

void timesup (int sig){
     done = 1;
}


int main() {
     done = 0;
     signal( SIGALRM, timesup);
     alarm(TIMETORUN);
     

     DataBase db = DataBase("../data/dummy-data.bin");
     cout<<"sorting by cat and ts"<<endl;
     db.SortByCatAndTS();
     cout<<"processing categories"<<endl;
     db.ProcessCategories();
     cout<<"sorting by ts"<<endl;
     db.SortByTS();
     
     QuerySet qset = QuerySet("../data/dummy-queries.bin", db);
     Query** queries = qset.GetQueries();
     int nq = qset.GetQueryCount();
     
     if (0) {
          int dummyswitch;
          for (int i = 0; i<nq; ++i)
               queries[i]->run(dummyswitch);
          qset.WriteOutput("../data/dummy-output-seqscanrange.bin");
     }
     else {
          QueryRunManager runManager (queries, nq, NTHREADS);
          runManager.run();
          qset.WriteOutput("../data/dummy-output-seqscanrangemt2.bin");
     }
     
     
     return 0;
}
