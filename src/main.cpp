#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "../include/constants.hpp"
#include "../include/data.hpp"



int main() {
    // Your code here

    std::cout << "VECTOR_SIZE: " << VECTOR_SIZE << std::endl;
    DataPoint a = DataPoint(1.0, 1, new float[DATA_size]); 
    std::cout << "DataPoint a timestamp: " << a.Get_c() << std::endl;

    return 0;
}