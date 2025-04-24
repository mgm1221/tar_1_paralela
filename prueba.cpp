#include <iostream>
#include <cstdlib>
#include <ctime>
#include "strassen_parallel.h"
#include "utility.h"

using namespace std;

int main() {
    srand(42);  // For reproducibility
    const int dim = 4;

    // ---------- Test 1: Random × Diagonal ----------
    cout << "=== Test 1: Random Matrix × Diagonal Matrix ===" << endl;

    int** A1 = new_mat(dim);
    int** B1 = new_mat(dim);

    // Fill A1 with random values (0–5)
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            A1[i][j] = rand() % 6;

    // Fill B1 as diagonal matrix with random values (0–5)
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            B1[i][j] = (i == j) ? (rand() % 6) : 0;

    int** C1 = Strassen_Matrix_Multiplication(A1, B1, dim);

    cout << "\nMatrix A1:" << endl;
    print_mat(A1, dim);

    cout << "\nMatrix B1 (Diagonal):" << endl;
    print_mat(B1, dim);

    cout << "\nA1 × B1 (Strassen):" << endl;
    print_mat(C1, dim);

    free_mat(A1, dim);
    free_mat(B1, dim);
    free_mat(C1, dim);

    // ---------- Test 2: Random × Random ----------
    cout << "\n\n=== Test 2: Random Matrix × Random Matrix ===" << endl;

    int** A2 = new_mat(dim);
    int** B2 = new_mat(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            A2[i][j] = rand() % 6;
            B2[i][j] = rand() % 6;
        }
    }

    int** C2 = Strassen_Matrix_Multiplication(A2, B2, dim);

    cout << "\nMatrix A2:" << endl;
    print_mat(A2, dim);

    cout << "\nMatrix B2:" << endl;
    print_mat(B2, dim);

    cout << "\nA2 × B2 (Strassen):" << endl;
    print_mat(C2, dim);

    free_mat(A2, dim);
    free_mat(B2, dim);
    free_mat(C2, dim);

    return 0;
}
