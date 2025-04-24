#ifndef UTILITY_H
#define  UTILITY_H

#include <iostream>
#include <chrono>
#include <cstdlib>  
#include <ctime>

int** initialize_mat(int rows, int cols);
int** new_mat(int size);
void free_mat(int** mat, int size);
int** multiply(int** A, int** B, int size);
int** add(int** A, int** B, int n);
int** sub(int** mat_a,int** mat_b,int dim);
void print_mat(int** mat, int dim);

#endif