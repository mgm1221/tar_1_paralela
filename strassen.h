#ifndef STRASSEN_H
#define STRASSEN_H

#include <tuple>

int** m1(int** a_1,int** a_2,int** b_1,int** b_2, int dim);
int** m2_m5(int** sum_1,int** sum_2, int** mul,int dim);
int** m3_m4(int** sub_1,int** sub_2, int** mul,int dim);
int** m6_m7(int** a_1,int** a_2,int** b_1,int** b_2, int dim);

std::tuple<int**,int**,int**,int**> separar_matriz(int** mat,int dim);
int** Strassen_Matrix_Multiplication(int** a, int** b, int dim);
int** Strassen_Matrix_Multiplication_parallel(int** a, int** b, int dim);

#endif
