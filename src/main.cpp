#include "DataBase.hpp"
#include "QuerySet.hpp"
#include <iostream>

using namespace std;



int main() {
    DataBase db = DataBase("../data/dummy-data.bin");
    db.SortByCatAndTS();
    
    QuerySet queries = QuerySet("../data/dummy-queries.bin");
    cout<<queries.GetQueryCount()<<endl;
    
    return 0;
}
