#include <iostream>
#include <sstream>
#include <iomanip>
#include <array>
#include "../include/Kmeans.hpp"
#include "../include/DataBase.hpp"
#include "../include/DataPoint.hpp"
#include <cassert>
//#include <vector>
//#include "Utils.hpp"

// void print_result_dkm(std::tuple<std::vector<float*>, std::vector<uint32_t>>& result) {
// 	std::cout << "centers: ";
// 	for (const auto& c : std::get<>(result)) {
// 		std::cout << "(";
// 		for (auto v : c) {
// 			std::cout << v << ",";
// 		}
// 		std::cout << "), ";
// 	}
// 	std::cout << std::endl;
// }

void runTests_closest_distance() {
   
    const double epsilon = 0.000001;

    // Add more test cases as needed...
    std::vector<float*> emptyMeans;
    std::vector<float*> emptyData;
    std::vector<float> result1 = closest_distance(emptyMeans, emptyData);
    assert(result1.empty());

    // Test case 2: Single mean and single data point
    float mean1[100] = {1.0};
    float data1[100] = {1.0};
    std::vector<float*> means2 = {mean1};
    std::vector<float*> data2 = {data1};
    std::vector<float> result2 = closest_distance(means2, data2);
    assert(result2.size() == 1);
    assert(result2[0] - 0 <= epsilon ); 
    // Test case 3: Multiple means and data points
    float mean2[100] = {0.0};
    float data3[100] = {1.0};
    float data4[100] = {-1.0};
    std::vector<float*> means3 = {mean1, mean2};
    std::vector<float*> data3_ = {data3, data4};
    std::vector<float> result3 = closest_distance(means3, data3_);
    assert(result3.size() == 2);
    assert(result3[0] - 100.0 <= epsilon ); // Distance between data3 and mean1
    assert(result3[1] - 100.0 <= epsilon); // Distance between data4 and mean2

    // Test case 4: Multiple means and data points

     float mean3[100] = {1.0};   
     float mean4[100] = {10.0};  

    float data5[100] = {2.0};
    float data6[100] = {5.0};

    std::vector<float*> means4 = {mean3, mean4};
    std::vector<float*> data4_ = {data5, data6};

    std::vector<float> result4 = closest_distance(means4, data4_);
    assert(result4.size() == 2);
    assert(result4[0] - 6.324555320336759 * 6.324555320336759  <= epsilon); // Distance between data5 and mean3
    assert(result4[1] - 39.242833740697165 * 39.242833740697165 <= epsilon); // Distance between data6 and mean4

    std::cout << "distance mean done!" << std::endl;


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

    std::cout << "Test closest mean done!" << std::endl;
}

void test_calculate_clusters() {
    // Cas de test 1: Aucune donnée
    std::vector<float*> emptyData;
    std::vector<float*> means1;
    std::vector<uint32_t> result1 = calculate_clusters(emptyData, means1);
    assert(result1.empty());

    // Cas de test 2: Un seul point de données avec une seule moyenne
    float mean1[100] = {1.0}; // Moyenne simple
    float data1[100] = {2.0}; // Point simple
    std::vector<float*> means2 = {mean1};
    std::vector<float*> data2 = {data1};
    std::vector<uint32_t> result2 = calculate_clusters(data2, means2);
    assert(result2.size() == 1);
    assert(result2[0] == 0); // Le seul point de données devrait appartenir à la première moyenne (index 0)

    // Cas de test 3: Plusieurs points de données avec plusieurs moyennes
    float mean2[100] = {0.0}; // Première moyenne
    float mean3[100] = {2.0}; // Deuxième moyenne
    float data3[100] = {1.0}; // Premier point de données
    float data4[100] = {3.0}; // Deuxième point de données
    std::vector<float*> means3 = {mean2, mean3};
    std::vector<float*> data3_ = {data3, data4};
    std::vector<uint32_t> result3 = calculate_clusters(data3_, means3);
    assert(result3.size() == 2);
    assert(result3[0] == 0); // Le premier point de données devrait appartenir à la première moyenne (index 0)
    assert(result3[1] == 1); // Le deuxième point de données devrait appartenir à la deuxième moyenne (index 1)

    // Ajoutez plus de cas de test selon vos besoins...
    std::cout << "Test calculate cluster done!" << std::endl;
}

void test_deltas() {
    // Cas de test 1: Aucun ancien moyen, aucun nouveau moyen
    std::vector<float*> old_means1;
    std::vector<float*> means1;
    std::vector<float> result1 = deltas(old_means1, means1);
    assert(result1.empty());

    // Cas de test 2: Un ancien moyen, un nouveau moyen
    float old_mean1[DATA_SIZE] = {}; // Initialisation avec zéros pour DATA_SIZE éléments
    float mean1[DATA_SIZE] = {}; // Initialisation avec zéros pour DATA_SIZE éléments
    std::vector<float*> old_means2 = {old_mean1};
    std::vector<float*> means2 = {mean1};
    std::vector<float> result2 = deltas(old_means2, means2);
    assert(result2.size() == 1);
    assert(result2[0] == distance(mean1, old_mean1));

    // Cas de test 3: Plusieurs anciens moyens, plusieurs nouveaux moyens
    float old_mean2[DATA_SIZE] = {}; // Initialisation avec zéros pour DATA_SIZE éléments
    float old_mean3[DATA_SIZE] = {}; // Initialisation avec zéros pour DATA_SIZE éléments
    float mean2[DATA_SIZE] = {}; // Initialisation avec zéros pour DATA_SIZE éléments
    float mean3[DATA_SIZE] = {}; // Initialisation avec zéros pour DATA_SIZE éléments
    std::vector<float*> old_means3 = {old_mean2, old_mean3};
    std::vector<float*> means3 = {mean2, mean3};
    std::vector<float> result3 = deltas(old_means3, means3);
    assert(result3.size() == 2);
    assert(result3[0] == distance(mean2, old_mean2));
    assert(result3[1] == distance(mean3, old_mean3 ));

    // Ajoutez plus de cas de test selon vos besoins...

    std::cout << "Test deltas done!" << std::endl;
}

void test_kmeans() {
    
    const char* pointsInput = "../data/dummy-data.bin";
    DataBase db = DataBase(pointsInput);
    std::vector<DataPoint> data_points = db.GetPoints();

    std::vector<float *> data;

    for (int i = 0; i < db.GetSize(); i++) {
        data.push_back(data_points[i].GetData());
    } 

     clustering_parameters parameters(100);
     parameters.set_min_delta(-1.0);
    
    auto cluster_data = kmeans_lloyd(data, parameters);

	// std::cout << "Means:" << std::endl;
	// for (const auto& mean : std::get<0>(cluster_data)) {
	// 	std::cout << "\t(" << mean[0] << "," << mean[1] << ")" << std::endl;
	// }
	// std::cout << "\nCluster labels:" << std::endl;
	// std::cout << "\tPoint:";
	// for (const auto& point : data) {
	// 	std::stringstream value;
	// 	value << "(" << point[0] << "," << point[1] << ")";
	// 	std::cout << std::setw(14) << value.str();
	// }
	// std::cout << std::endl;
	// std::cout << "\tLabel:";
	// for (const auto& label : std::get<1>(cluster_data)) {
	// 	std::cout << std::setw(14) << label;
	// }
	// std::cout << std::endl;

    std::cout << "Test kmeans done!" << std::endl;
}

volatile int done = 0;

int main() {
    // Your code here
    runTests_closest_distance();
    test_closest_mean();
    test_calculate_clusters();
    test_deltas();
    test_kmeans();
    

    return 0;
}