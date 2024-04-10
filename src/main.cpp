#include "DataBase.hpp"
#include <iostream>

using namespace std;



int main() {
    cout<<"start"<<endl;
    DataBase db = DataBase("../data/dummy-data.bin");
    cout<<"end"<<endl;
    
    return 0;
}
