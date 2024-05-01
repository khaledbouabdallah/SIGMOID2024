#include <iostream>
#include <array>
#include "../include/Kmeans.hpp"
//#include "Utils.hpp"


volatile int done = 0;

int main() {
    // Your code here

     float a[10] = {-1,-1,0,0,0,6,7,8,9,10};
     float b[10] = {1,2,3,4,5,6,7,8,9,10};



    //float distance = getDistance(a, b);
    float distance = distance_squared(a, b);
    printf("%f",distance);






    

    return 0;
}