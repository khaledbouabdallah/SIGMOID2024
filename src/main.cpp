#include "DataBase.hpp"
#include <iostream>

using namespace std;



int main() {
    DataBase db = DataBase("../data/dummy-data.bin");
    db.SortByCatAndTS();
    
    return 0;
}
