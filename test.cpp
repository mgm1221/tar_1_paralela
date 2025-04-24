#include <iostream>
#include <chrono>
#include <cstdlib>  
#include <ctime>

using namespace std;


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

int* multiply_cache_friendly(int* A, int* B, int size) {
    int* C = new int[size * size]();

    for (int i = 0; i < size; ++i)
        for (int k = 0; k < size; ++k)
            for (int j = 0; j < size; ++j)
                C[i * size + j] += A[i * size + k] * B[k * size + j];

    return C;
}

int main(){

    for(int i = 8; i <= 1024; i*=2){
       
        double time = 0;

        int* A; 
        int* B;
    
        for(int j = 0; j < 10; j++){

            A = initialize_mat(i, i); 
            B = initialize_mat(i, i);

            auto start = chrono::high_resolution_clock::now();
            int* result = multiply_cache_friendly(A, B, i);
            auto end = chrono::high_resolution_clock::now();

            double duration_ms = static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end - start).count());

		    time += duration_ms;

            delete[] result;

        }

		time =  time / 100;

        cout<<"Size: " << i << ", Time cache frienly: " << time << endl; 

        delete[] A;
        delete[] B;


    }

    return 0;
}
