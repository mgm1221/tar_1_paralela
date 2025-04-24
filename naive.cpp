#include <iostream>
#include <chrono>
#include <cstdlib>  
#include <ctime>

using namespace std;

int** new_mat(int size){

    int** mat = new int*[size];
    
    for (int i = 0; i < size; i++){
        mat[i] = new int[size];
    }

    return mat;
}

void free_mat(int** mat, int size) {

    for (int i = 0; i < size; i++)
        delete[] mat[i];
    delete[] mat;

}

int** initialize_mat(int rows, int cols){

    srand(time(NULL));

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

int** multiply(int** A, int** B, int size) {

    int** C = new_mat(size);

    for (int i = 0; i < size; ++i)
        for (int k = 0; k < size; ++k)
            for (int j = 0; j < size; ++j)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}


int main(){

    for(int i = 1600; i <= 1601; i+=50){
       
        double time = 0;

        int** A; 
        int** B;
    
        for(int j = 0; j < 1; j++){

            A = initialize_mat(i, i); 
            B = initialize_mat(i, i);

            //auto start = chrono::high_resolution_clock::now();
            int** result = multiply(A, B, i);
            //auto end = chrono::high_resolution_clock::now();

            //double duration_ms = static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end - start).count());

		    //time += duration_ms;


            for (int k = 0; k < k; k++) {
                delete[] result[k];

            }

            delete[] result;

        }

		time =  time / 100;

        //cout<<"Size: " << i << ", Time naive: " << time << endl; 


        for (int k = 0; k < k; k++) {
            delete[] A[k];
            delete[] B[k];


        }
        delete[] A;
        delete[] B;


    }

    return 0;
}
