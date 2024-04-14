#include "DataBase.hpp"
#include "QuerySet.hpp"
#include "Query.hpp"
#include <iostream>
#include <fstream>

using namespace std;


int done = 0;

#define NTHREAD


int main() {
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
          
     qset.WriteOutput("../data/dummy-output-seqscan.bin");
     
     return 0;
}
