#ifndef BLOCKS_H
#define BLOCKS_H

int** merge(int** C1, int** C2, int** C3, int** C4, int size);

int** Block_Matrix_Multiplication(int** A, int** B, int size, int min_Size);
int** Block_Matrix_Multiplication_Parallel(int** A, int** B, int size, int min_Size);

#endif