#include <stdio.h>
#include <stdint.h>

#define VECTOR_DIMENSION 100
#define MAX_VECTOR_SIZE (102 * sizeof(float))

int main() {
    
    // Open the binary file for reading
    FILE *file = fopen("../data/dummy-data.bin", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the number of vectors
    uint32_t num_vectors;
    if (fread(&num_vectors, sizeof(uint32_t), 1, file) != 1) {
        perror("Error reading num_vectors");
        fclose(file);
        return 1;
    }

    printf("Number of vectors: %u\n", num_vectors);

    // // Read the first vector
    // float dimensions[2]; // Array to store C and T dimensions
    // float vector[VECTOR_DIMENSION]; // Array to store the vector data

    // // Read C and T dimensions
    // if (fread(dimensions, sizeof(float), 2, file) != 2) {
    //     perror("Error reading dimensions");
    //     fclose(file);
    //     return 1;
    // }

    // printf("Vector 1: C = %f, T = %f, ", dimensions[0], dimensions[1]);

    // // Read the rest of the vector
    // if (fread(vector, sizeof(float), VECTOR_DIMENSION, file) != VECTOR_DIMENSION) {
    //     perror("Error reading vector");
    //     fclose(file);
    //     return 1;
    // }

    // // Print the vector data
    // printf("Vector data: ");
    // for (int j = 0; j < VECTOR_DIMENSION; j++) {
    //     printf("%f ", vector[j]);
    // }
    // printf("\n");

    // Close the file
    fclose(file);

    return 0;
}
