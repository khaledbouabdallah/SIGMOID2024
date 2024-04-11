#include "DataBase.hpp"
#include "QuerySet.hpp"
#include <iostream>
#include <iomanip>

using namespace std;



int main() {
    DataBase db = DataBase("../data/dummy-data.bin");
    db.SortByCatAndTS();
    db.NormalizeData();
    
    QuerySet queries = QuerySet("../data/dummy-queries.bin", db);
    cout<<queries.GetQueryCount()<<endl;
    
    return 0;
}
