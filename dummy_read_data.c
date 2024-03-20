#include <stdio.h>
#include <stdint.h>

#define VECTOR_DIMENSION 102
#define MAX_VECTOR_SIZE (VECTOR_DIMENSION * sizeof(float))

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

    // Create a vector to hold all the vectors
    float vectors[num_vectors][VECTOR_DIMENSION];

    // Read each vector
    for (int i = 0; i < num_vectors; i++) {
        if (fread(vectors[i], sizeof(float), VECTOR_DIMENSION, file) != VECTOR_DIMENSION) {
            perror("Error reading vectors");
            fclose(file);
            return 1;
        }
    }

    // print first vector
    printf("Vector 1: ");
    for (int j = 0; j < VECTOR_DIMENSION; j++) {
        printf("%f ", vectors[0][j]);
    }

    // Close the file
    fclose(file);

    return 0;
}
