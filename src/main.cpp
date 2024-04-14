#include "DataBase.hpp"
#include "QuerySet.hpp"
#include "Query.hpp"
#include "globals.hpp"
#include <signal.h>
#include <iostream>
#include <fstream>

using namespace std;


volatile int done = 0;


void timesup (int sig){
     done = 1;
}


int main() {
     done = 0;
     signal( SIGALRM, timesup);
     alarm(MINSTORUN*60);
     

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
     
     //ofstream ofs("bla");
     int dummyswitch;
     for (int i = 0; i<nq; ++i) {
          //cout<<"running query "<<i<<endl;
          queries[i]-> run(dummyswitch);
          //queries[i]->WriteOutput(ofs);
     }
     
    // while (!done) {}
     
          
     qset.WriteOutput("../data/dummy-output-seqscanrange.bin");
     
     return 0;
}
