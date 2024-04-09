#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "../include/constants.hpp"
#include "../include/data.hpp"





int main() {

    std::cout << "VECTOR_SIZE: " << VECTOR_SIZE << std::endl;
    std::cout << "QUERY_SIZE: " << QUERY_SIZE << std::endl;
    std::cout << "DATA_SIZE: " << DATA_SIZE << std::endl;
    std::cout << "Number of nearest neighbors to find: " << K << std::endl;


    DataPoint a = DataPoint(1.0, 1, new float[DATA_SIZE]); 
    std::cout << "DataPoint a timestamp: " << a.Get_c() << std::endl;

    // init database
    DataBase db = DataBase(std::vector<DataPoint>());
    // read data from file and sort them while reading TODO
    db.Read_data_from_file("../data/dummy-data.bin");  // We have sorted data 
   // Read queries TODO



    return 0;
}