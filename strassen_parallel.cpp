#include <iostream>
#include <tuple>
#include <omp.h>
#include "strassen.h"
#include "utility.h"

using namespace std;

	

int** Strassen_Matrix_Multiplication_parallel(int** a, int** b,int dim){
	
	int** result = new_mat(dim);
	int** A_11, **A_12, **A_21, **A_22;
	int** B_11, **B_12, **B_21, **B_22;
	
	int mitad = dim / 2;
	int** M_1, **M_2, **M_3, **M_4, **M_5, **M_6, **M_7;
	int** C_11,**C_12,**C_21,**C_22;

	#pragma omp parallel
	{
       		#pragma omp single
		{
			#pragma omp task
			{ 
				tie(A_11,A_12,A_21,A_22)= separar_matriz(a, dim); 
			}
			#pragma omp task
        		{tie(B_11, B_12, B_21, B_22) = separar_matriz(b, dim);}

	        	#pragma omp taskwait

        		#pragma omp task
			{M_1 = m1(A_11, A_22, B_11, B_22, mitad);}
	
        		#pragma omp task
			{M_2 = m2_m5(A_21, A_22, B_11, mitad);}

        		#pragma omp task
			{M_3 = m3_m4(B_12, B_22, A_11, mitad);}

	        	#pragma omp task
			{M_4 = m3_m4(B_21, B_11, A_22, mitad);}

        		#pragma omp task
			{M_5 = m2_m5(A_11, A_12, B_22, mitad);}

        		#pragma omp task
			{M_6 = m6_m7(A_21, A_11, B_11, B_12, mitad);}
		
	        	#pragma omp task
			{M_7 = m6_m7(A_12, A_22, B_21, B_22, mitad);}

       		 	#pragma omp taskwait
		
			#pragma omp task
			{C_11 = add(sub(add(M_1, M_4, mitad), M_5, mitad), M_7, mitad);}
			#pragma omp task
	    		{C_12 = add(M_3, M_5, mitad);}				
			#pragma omp task
			{C_21 = add(M_2, M_4, mitad);}
			#pragma omp task
			{C_22 = add(add(sub(M_1, M_2, mitad), M_3, mitad), M_6, mitad);}
			#pragma omp taskwait
    		}
	}
    	for (int i = 0; i < mitad; i++) {
        	for (int j = 0; j < mitad; j++) {
            		result[i][j] = C_11[i][j];
            		result[i][j + mitad] = C_12[i][j];
            		result[i + mitad][j] = C_21[i][j];
            		result[i + mitad][j + mitad] = C_22[i][j];
        	}
    	}	

    	return result;


}
