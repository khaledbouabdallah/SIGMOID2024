#include "DataBase.hpp"
#include "QuerySet.hpp"
#include <iostream>

using namespace std;



int main() {
    DataBase db = DataBase("../data/dummy-data.bin");
    cout<<"sorting by cat and ts"<<endl;
    db.SortByCatAndTS();
    cout<<"processing categories"<<endl;
    db.ProcessCategories();
    cout<<"sorting by ts"<<endl;
    db.SortByTS();
    
    QuerySet queries = QuerySet("../data/dummy-queries.bin", db);
    queries.WriteOutput("../data/dummy-output.bin");
    
    return 0;
}
