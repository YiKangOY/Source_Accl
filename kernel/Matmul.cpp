#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"
#include <iostream>
using namespace std;
/* template<int m1, int m2, int b1, int b2>
void Matmul(Data_t A[m1][m2], Data_t B[m2][m1], Data_t C[m1][m1]){

    //Local variables
    Data_t LocalA[m1][m2], LocalB[m2][m1], LocalC[m1][m1];

    Data_t Block_out[b1][b1];

    
    #pragma HLS ARRAY_PARTITION variable = LocalA dim = 1 complete
    #pragma HLS ARRAY_PARTITION variable = LocalB dim = 2 complete
    #pragma HLS ARRAY_PARTITION variable = LocalC dim = 0 complete

    //std::cout<<*A<<std::endl;

    //Read to local
    for(int i = 0; i < m2; i++){
        for(int j = 0; j < m1; j++){
            LocalA[j][i] = A[j][i];
        }
    }

    for(int i = 0; i < m2; i++){
        for(int j = 0; j < m1; j++){
            LocalB[i][j] = B[i][j];
        }
    }

    for(int i = 0; i < m1; i++){
        for(int j = 0; j < m1; j++){
            LocalC[i][j] = 0;
        }
    }

    //Call systolic array in a tiled shceme
    LpC_it1:
    for(int it1 = 0; it1 < m1; it1 = it1 + b1){
        //@todo: add it later, may cause syth slow #pragma HLS UNROLL
        #pragma HLS PIPELINE off
    	LpC_it2:
        for(int it2 = 0; it2 < m1; it2 = it2 + b1){
        //@todo: add it later, may cause syth slow #pragma HLS UNROLL
            //it1 and it2 are used to locate target output in C matrix
            #pragma HLS PIPELINE off
        	LpC_loc:
            for(int loc = 0; loc < m2; loc = loc + b2){
			#pragma HLS LOOP_FLATTEN off
            #pragma HLS PIPELINE off
			
                //Blocks in a row (one row has K cols, divide by b2)

                //Feed A to systolic array
                Data_t TempA [b1][b2];
                #pragma HLS ARRAY_PARTITION variable = TempA dim = 1 complete
            	FeedA1:
                for(int col = 0; col < b2; col++){
                	FeedA2:
                    for(int row = 0; row < b1; row++){
                        TempA[row][col] = LocalA[it1 + row][col + loc];
                    }
                }

                //Feed B to systolic array
                Data_t TempB [b2][b1];
                #pragma HLS ARRAY_PARTITION variable = TempB dim = 1 complete
                FeedB1:
                for(int row = 0; row < b2; row++){
                	FeedB2:
                    for(int col = 0; col < b1; col++){
                        TempB[row][col] = LocalB[row + loc][it2 + col];
                    }

                }

                Blockmatmul<b1, b2>(TempA, TempB, Block_out);

                PS1:
                for(int i = 0; i < b1; i++){
                	PS2:
                    for(int j = 0; j < b1; j++){
                        LocalC[it1 + i][it2 + j] += Block_out[i][j];
                    }
                }
            }
        }
    }
    //Systolic array finish

    //#pragma HLS ARRAY_PARTITION variable = LocalC dim = 0 complete
     Wout1:
    for(int i = 0; i < m1; i++){
    	Wout2:
        for(int j = 0; j < m1; j++){
            C[i][j] = LocalC[i][j];
        }
    }

}

 */

void Wrapper(Data_t A[Mat_SizeM][Mat_SizeK], Data_t B[Mat_SizeK][Mat_SizeM], Data_t C[Mat_SizeM][Mat_SizeM]){
    Matmul<Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_K> (A, B, C);
}