#include <iostream>
#include <array>
#include "../include/Kmeans.hpp"
#include <cassert>
//#include "Utils.hpp"


void runTests_closest_distance() {
   
    const double epsilon = 0.000001;

    // Add more test cases as needed...
    std::vector<float*> emptyMeans;
    std::vector<float*> emptyData;
    std::vector<float> result1 = closest_distance(emptyMeans, emptyData);
    assert(result1.empty());

    // Test case 2: Single mean and single data point
    float mean1[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    float data1[10] = {3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    std::vector<float*> means2 = {mean1};
    std::vector<float*> data2 = {data1};
    std::vector<float> result2 = closest_distance(means2, data2);
    assert(result2.size() == 1);
    std::cout << result2[0] << std::endl;
    assert(result2[0] - 6.32456 <= epsilon ); // Expected distance is sqrt(1^2 + 2^2 + ..
    // Test case 3: Multiple means and data points
    float mean2[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float data3[10] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    float data4[10] = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0};
    std::vector<float*> means3 = {mean1, mean2};
    std::vector<float*> data3_ = {data3, data4};
    std::vector<float> result3 = closest_distance(means3, data3_);
    assert(result3.size() == 2);
    assert(result3[0] - 3.1622776601683795  <= epsilon ); // Distance between data3 and mean1
    assert(result3[1] - 3.1622776601683795 <= epsilon); // Distance between data4 and mean2

    // Test case 4: Multiple means and data points

     float mean3[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};   
     float mean4[10] = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0};  

    float data5[10] = {3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    float data6[10] = {-1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0, -10.0};

    std::vector<float*> means4 = {mean3, mean4};
    std::vector<float*> data4_ = {data5, data6};

    std::vector<float> result4 = closest_distance(means4, data4_);
    assert(result4.size() == 2);
    assert(result4[0] - 6.324555320336759 <= epsilon); // Distance between data5 and mean3
    assert(result4[1] - 39.242833740697165 <= epsilon); // Distance between data6 and mean4


}

void test_closest_mean() {
    // Cas de test 1: Un seul point avec un seul point de moyenne
    float mean1[100] = {1.0}; // Moyenne simple
    float point1[100] = {2.0}; // Point simple
    std::vector<float*> means1 = {mean1};
    uint32_t result1 = closest_mean(point1, means1);
    
    assert(result1 == 0); // La moyenne la plus proche devrait être la première (index 0)

    // Cas de test 2: Plusieurs moyennes avec un seul point
    float mean2[100] = {0.0}; // Première moyenne
    float mean3[100] = {2.0}; // Deuxième moyenne
    std::vector<float*> means2 = {mean2, mean3};
    uint32_t result2 = closest_mean(point1, means2);
    std::cout << result2 << std::endl;
    assert(result2 == 1); // La moyenne la plus proche devrait être la première (index 0)

    // Ajoutez plus de cas de test selon vos besoins...

    std::cout << "Tous les tests sont passés avec succès!" << std::endl;
}

volatile int done = 0;

int main() {
    // Your code here
    test_closest_mean();
    

    return 0;
}