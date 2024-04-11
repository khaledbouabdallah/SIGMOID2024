#include "DataBase.hpp"
#include <iostream>
#include <iomanip>

using namespace std;



int main() {
    DataBase db = DataBase("../data/dummy-data.bin");
    db.SortByCatAndTS();
    db.NormalizeData();
    
    return 0;
}
