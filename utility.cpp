#include "utility.h"

int** initialize_mat(int rows, int cols){

    srand(7);

    int** matrix = new int*[rows];

    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }

    return matrix;

}

int** new_mat(int size) {
    int** mat = new int*[size];

    for (int i = 0; i < size; i++) {
        mat[i] = new int[size];
        std::fill(mat[i], mat[i] + size, 0);

    }

    return mat;
}


void free_mat(int** mat, int size) {

    for (int i = 0; i < size; i++)
        delete[] mat[i];
    delete[] mat;

}

int** multiply(int** A, int** B, int size) {

    int** C = new_mat(size);

    for (int i = 0; i < size; ++i)
        for (int k = 0; k < size; ++k)
            for (int j = 0; j < size; ++j)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

int** add(int** A, int** B, int n) {

    int** result = new_mat(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    return result;

}

int** sub(int** A, int** B, int size){

    int** result = new_mat(size);

    for(int i =0; i < size; i++){
        for(int j=0; j < size; j++){
            result[i][j] = A[i][j] - B[i][j];

        }

    }

    return result;
}

void print_mat(int** mat, int dim) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j)
            std::cout << mat[i][j] << " ";
        std::cout << std::endl;
    }
}
