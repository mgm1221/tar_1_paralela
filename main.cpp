#include "blocks.h"
#include "strassen.h"
#include "utility.h"




using namespace std;




int main() {




    srand(time(nullptr));
   
    for(int i = 8; i <= 256; i*=2){
       
        double time_blocks = 0;
        double time_blocks_parallel = 0;
        double time_strassen = 0;
        double time_strassen_parallel = 0;

        int** A = initialize_mat(i, i);
        int** B = initialize_mat(i, i);
       
        for(int j = 0; j < 10; j++){

            auto start = chrono::high_resolution_clock::now();
            int** result_blocks = Block_Matrix_Multiplication(A, B, i, i>>2);
            auto end = chrono::high_resolution_clock::now();

            double duration_ms = static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end - start).count());

		    time_blocks += duration_ms;


            start = chrono::high_resolution_clock::now();
            int** result_blocks_parallel = Block_Matrix_Multiplication_Parallel(A, B, i, i>>2);
            end = chrono::high_resolution_clock::now();

            duration_ms = static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end - start).count());

		    time_blocks_parallel += duration_ms;


            start = chrono::high_resolution_clock::now();
            int** result_strassen = Strassen_Matrix_Multiplication(A, B ,i);
            end = chrono::high_resolution_clock::now();

		    duration_ms = static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end - start).count());

		    time_strassen += duration_ms;
		
		start = chrono::high_resolution_clock::now();
            	int** result_strassen_parallel = Strassen_Matrix_Multiplication(A, B ,i);
            	end = chrono::high_resolution_clock::now();

                    duration_ms = static_cast<double>(chrono::duration_cast<chrono::milliseconds>(end - start).count());

                    time_strassen_parallel += duration_ms;	

            for (int k = 0; k < k; k++) {

                delete[] result_blocks[k];
                delete[] result_blocks_parallel[k];
                delete[] result_strassen[k];
		delete[] result_strassen_parallel[k];
   
   
            }

            delete[] result_blocks;
            delete[] result_blocks_parallel;
            delete[] result_strassen;
	    delete[] result_strassen_parallel;
        }

		time_blocks =  time_blocks / 10;
        time_blocks_parallel =  time_blocks_parallel / 10;
        time_strassen = time_strassen / 10;
	time_strassen_parallel = time_strassen_parallel/10;
	
        cout<<"Size: " << i << ", Time blocks: " << time_blocks <<", Time blocks parallel: "<< time_blocks_parallel << ", Time strassen: " << time_strassen << ", Time strassen parallel: " <<time_strassen_parallel << endl; 


        for (int k = 0; k < k; k++) {
            delete[] A[k];
            delete[] B[k];


        }
        delete[] A;
        delete[] B;


    }
    return 0;
}







