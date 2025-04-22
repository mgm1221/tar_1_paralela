#include <iostream>
#include <tuple>
using namespace std;
void free_matriz(int** matriz, int dim) {
    for (int i = 0; i < dim; ++i) {
        delete[] matriz[i];
    }
    delete[] matrix;
}
int** creacion_matriz(int dim){
	int** matrix = new int*[dim];

        for(int i  = 0;i<dim; i++){
                matrix[i] = new int[dim];
        }
	return matrix;
}

int** multiplication(int** mat_a, int** mat_b,int dim){
	int** result = creacion_matriz(dim);

	for(int i =0; i< dim ; i++){

		for (int j = 0; j< dim; j++){
		
			result[i][j] = 0;
		
			for(int x =0;x < dim;x++){
		
		 		result[i][j] += mat_a[i][x] * mat_b[x][j];	
		
			}
		}		

	}
	return result;
}

int** sum(int** mat_a,int** mat_b,int dim){
	
	int** result = creacion_matriz(dim);

	for(int i =0;i<dim;i++){
	
		for(int j=0;j<dim;j++){
		
			result[i][j] = mat_a[i][j] + mat_b[i][j];

		}
	
	}
	return result;
}
int** sub(int** mat_a,int** mat_b,int dim){

        int** result = creacion_matriz(dim);

        for(int i =0;i<dim;i++){

                for(int j=0;j<dim;j++){

                        result[i][j] = mat_a[i][j] - mat_b[i][j];

                }

        }
	return result;
}
int** m1(int** a_1,int** a_2,int** b_1,int** b_2, int dim){

	int** sub_matriz_1 = sum(a_1,a_2,dim);

	int** sub_matriz_2 = sum(b_1,b_2,dim);

	int** result = multiplication(sub_matriz_1,sub_matriz_2,dim);
	free_matriz(sub_matriz_1);
	free_matriz(sub_matriz_2);
	return result;

}
int** m2_m5(int** sum_1,int** sum_2, int** mul,int dim){
	int** sub_matriz = sum(sum_1,sum_2,dim);
	
	int** result = multiplication(sub_matriz,mul,dim);
	free_matriz(sub_matriz);
	return result;
}
int** m3_m4(int** sub_1,int** sub_2, int** mul,int dim){
	int** sub_matriz = sub(sub_1,sub_2,dim);

        int** result = multiplication(sub_matriz,mul,dim);
	free_matriz(sub_matriz);
        return result;
}
int** m6_m7(int** a_1,int** a_2,int** b_1,int** b_2, int dim){
	int** sub_matriz_1 = sub(a_1,a_2,dim);

        int** sub_matriz_2 = sum(b_1,b_2,dim);

        int** result = multiplication(sub_matriz_1,sub_matriz_2,dim);
	
	free_matriz(sub_matriz_1);
	free_matriz(sub_matriz_2);
        
	return result;

}
tuple<int**,int**,int**,int**> separar_matriz(int** mat,int dim){
	



}


void printMatrix(int** mat, int dim) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}


















