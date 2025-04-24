#include <iostream>
#include <chrono>
#include <cstdlib>  
#include <ctime>
#include <omp.h>

#include "blocks.h"
#include "utility.h"

using namespace std;


int** Block_Matrix_Multiplication_Parallel(int** A, int** B, int size, int min_size){

    int new_size = size / 2;

    int** A1 = new_mat(new_size);
    int** A2 = new_mat(new_size);
    int** A3 = new_mat(new_size);
    int** A4 = new_mat(new_size);

    int** B1 = new_mat(new_size);
    int** B2 = new_mat(new_size);
    int** B3 = new_mat(new_size);
    int** B4 = new_mat(new_size);

    //#pragma omp parallel for collapse(2)
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (i < new_size && j < new_size){
                    A1[i][j] = A[i][j];
                    B1[i][j] = B[i][j];
                    
                }
                else if (i < new_size && j >= new_size){
                    A2[i][j-new_size] = A[i][j];
                    B2[i][j-new_size] = B[i][j];

                }
                else if (i >= new_size && j < new_size){
                    A3[i-new_size][j] = A[i][j];
                    B3[i-new_size][j] = B[i][j];

                }
                else{
                    A4[i-new_size][j-new_size] = A[i][j];
                    B4[i-new_size][j-new_size] = B[i][j];

                }
            }
        }

    if (new_size == min_size){

        int** C1, **C2, **C3, **C4;

        #pragma omp parallel sections
        {

            #pragma omp section
            {
                int** C1_part1 = multiply(A1, B1, new_size);
                int** C1_part2 = multiply(A2, B3, new_size);
                C1 = add(C1_part1, C1_part2, new_size);

                free_mat(C1_part1, new_size); free_mat(C1_part2, new_size);

            }

            #pragma omp section
            {
                int** C2_part1 = multiply(A1, B2, new_size);
                int** C2_part2 = multiply(A2, B4, new_size);
                C2 = add(C2_part1, C2_part2, new_size);

                free_mat(C2_part1, new_size); free_mat(C2_part2, new_size);

            }
            #pragma omp section
            {    
                int** C3_part1 = multiply(A3, B1, new_size);
                int** C3_part2 = multiply(A4, B3, new_size);
                C3 = add(C3_part1, C3_part2, new_size);

                free_mat(C3_part1, new_size); free_mat(C3_part2, new_size);

            }

            #pragma omp section
            {
                int** C4_part1 = multiply(A3, B2, new_size);
                int** C4_part2 = multiply(A4, B4, new_size);
                C4 = add(C4_part1, C4_part2, new_size);

                free_mat(C4_part1, new_size); free_mat(C4_part2, new_size);

            }

        }

        int** C = merge(C1, C2, C3, C4, new_size);

        free_mat(A1, new_size); free_mat(A2, new_size);
        free_mat(A3, new_size); free_mat(A4, new_size);
        free_mat(B1, new_size); free_mat(B2, new_size);
        free_mat(B3, new_size); free_mat(B4, new_size);

        free_mat(C1, new_size); free_mat(C2, new_size); free_mat(C3, new_size); free_mat(C4, new_size); 

        return C;
        
    }

    else{

        int** C1, **C2, **C3, **C4;

        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                #pragma omp task
                {
                    int** C1_part1 = Block_Matrix_Multiplication_Parallel(A1, B1, new_size, min_size);
                    int** C1_part2 = Block_Matrix_Multiplication_Parallel(A2, B3, new_size, min_size);
                    C1 = add(C1_part1, C1_part2, new_size);
                    free_mat(C1_part1, new_size); free_mat(C1_part2, new_size);
                }

                #pragma omp task
                {
                    int** C2_part1 = Block_Matrix_Multiplication_Parallel(A1, B2, new_size, min_size);
                    int** C2_part2 = Block_Matrix_Multiplication_Parallel(A2, B4, new_size, min_size);
                    C2 = add(C2_part1, C2_part2, new_size);
                    free_mat(C2_part1, new_size); free_mat(C2_part2, new_size);
                }

                #pragma omp task
                {
                    int** C3_part1 = Block_Matrix_Multiplication_Parallel(A3, B1, new_size, min_size);
                    int** C3_part2 = Block_Matrix_Multiplication_Parallel(A4, B3, new_size, min_size);
                    C3 = add(C3_part1, C3_part2, new_size);
                    free_mat(C3_part1, new_size); free_mat(C3_part2, new_size);
                }

                #pragma omp task
                {
                    int** C4_part1 = Block_Matrix_Multiplication_Parallel(A3, B2, new_size, min_size);
                    int** C4_part2 = Block_Matrix_Multiplication_Parallel(A4, B4, new_size, min_size);
                    C4 = add(C4_part1, C4_part2, new_size);
                    free_mat(C4_part1, new_size); free_mat(C4_part2, new_size);
                }

                #pragma omp taskwait
            }
        }

        int** C = merge(C1, C2, C3, C4, new_size);

        free_mat(A1, new_size); free_mat(A2, new_size);
        free_mat(A3, new_size); free_mat(A4, new_size);
        free_mat(B1, new_size); free_mat(B2, new_size);
        free_mat(B3, new_size); free_mat(B4, new_size);

        free_mat(C1, new_size); free_mat(C2, new_size); free_mat(C3, new_size); free_mat(C4, new_size); 

        return C;

    }

}


