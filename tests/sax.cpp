#include <iostream>
#include "../include/SAX.hpp"

volatile int done = 0;

int main() {
    // Your code here

    float data[10] = {-1,-1,0,0,0,6,7,8,9,10};
    //float data[10] = {1,2,3,4,5,6,7,8,9,10};


    SAX *sax = new SAX(2, 3);
    float* paa = sax->ToPAA(data, 10);

    int*  saxx = sax->ToSAX(paa, 2);

    for (int i = 0; i < 2; i++) {
        std::cout << paa[i] << " ";
    }
    std::cout << "" << "\n";
    for (int i = 0; i < 2; i++) {
        std::cout << saxx[i] << std::endl;
    }

    return 0;
}