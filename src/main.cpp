#include "DataBase.hpp"
#include "QuerySet.hpp"
#include "Query.hpp"
#include <iostream>

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
     
     int dummyswitch;
     for (int i = 0; i<nq; ++i) {
          //cout<<"running query "<<i<<endl;
          queries[i]-> run(dummyswitch);
     }
          
     qset.WriteOutput("../data/dummy-output-seqscanrange.bin");
     
     return 0;
}
