#include <iostream>
#include <chrono>
#include <cstdlib>  
#include <ctime>

using namespace std;

void flush_cache() {
    const size_t cache_size = 32 * 1024 * 1024;
    char* dummy = new char[cache_size];

    for (size_t i = 0; i < cache_size; ++i) {
        dummy[i] = i;
    }

    volatile char sink = 0;
    for (size_t i = 0; i < cache_size; ++i) {
        sink ^= dummy[i];
    }

    delete[] dummy;
}

void free_mat(int** mat, int size) {
    for (int i = 0; i < size; i++)
        delete[] mat[i];
    delete[] mat;
}

int* initialize_mat(int rows, int cols) {
    srand(time(NULL));

    int* matrix = new int[rows * cols];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = rand() % 100 + 1;
        }
    }

    return matrix;
}

void transpose(int* B, int* B_T, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            B_T[j * size + i] = B[i * size + j];
}

int* multiply_cache_friendly(int* A, int* B, int size) {
    int* C = new int[size * size]();

    for (int i = 0; i < size; ++i)
        for (int k = 0; k < size; ++k)
            for (int j = 0; j < size; ++j)
                C[i * size + j] += A[i * size + k] * B[k * size + j];

    return C;
}

int main() {
    int i  = 500;

    double time = 0;

    int* A;
    int* B;

    for (int j = 0; j < 10; j++) {

        A = initialize_mat(i, i);
        B = initialize_mat(i, i);

        flush_cache();
        auto start = chrono::high_resolution_clock::now();
        int* result = multiply_cache_friendly(A, B, i);
        auto end = chrono::high_resolution_clock::now();

        double duration_ms = static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end - start).count());

        time += duration_ms;

        delete[] result;
    }

    time = time / 10;

    cout << "Size: " << i << ", Time cache friendly: " << time << " ms" << endl;

    delete[] A;
    delete[] B;
    

    return 0;

}
