#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"
#include <iostream>
using namespace std;
void Matmul(Data_t A[Mat_SizeM][Mat_SizeK], Data_t B[Mat_SizeK][Mat_SizeM], Data_t C[Mat_SizeM][Mat_SizeM]){

    //Local variables
    Data_t LocalA[Mat_SizeM][Mat_SizeK], LocalB[Mat_SizeK][Mat_SizeM], LocalC[Mat_SizeM][Mat_SizeM];

    Data_t Block_out[Block_Size_M][Block_Size_M];

    //Local stream variable to matrix
    #pragma HLS ARRAY_PARTITION variable = LocalA dim = 1 complete
    #pragma HLS ARRAY_PARTITION variable = LocalB dim = 2 complete
    #pragma HLS ARRAY_PARTITION variable = LocalC dim = 0 complete

    //std::cout<<*A<<std::endl;

    //Read to local
    for(int i = 0; i < Mat_SizeK; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            LocalA[j][i] = A[j][i];
        }
    }

    for(int i = 0; i < Mat_SizeK; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            LocalB[i][j] = B[i][j];
        }
    }

    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            LocalC[i][j] = 0;
        }
    }

    //Call systolic array in a tiled shceme
    LpC_it1:
    for(int it1 = 0; it1 < Mat_SizeM; it1 = it1 + Block_Size_M){
        //@todo: add it later, may cause syth slow #pragma HLS UNROLL
        #pragma HLS PIPELINE off
    	LpC_it2:
        for(int it2 = 0; it2 < Mat_SizeM; it2 = it2 + Block_Size_M){
        //@todo: add it later, may cause syth slow #pragma HLS UNROLL
            //it1 and it2 are used to locate target output in C matrix
            #pragma HLS PIPELINE off
        	LpC_loc:
            for(int loc = 0; loc < Mat_SizeK; loc = loc + Block_Size_K){
			#pragma HLS LOOP_FLATTEN off
            #pragma HLS PIPELINE off
			
                //Blocks in a row (one row has K cols, divide by block_size_k)

                //Feed A to systolic array
                Data_t TempA [Block_Size_M][Block_Size_K];
                #pragma HLS ARRAY_PARTITION variable = TempA dim = 1 complete
            	FeedA1:
                for(int col = 0; col < Block_Size_K; col++){
                	FeedA2:
                    for(int row = 0; row < Block_Size_M; row++){
                        TempA[row][col] = LocalA[it1 + row][col + loc];
                    }
                }

                //Feed B to systolic array
                Data_t TempB [Block_Size_K][Block_Size_M];
                #pragma HLS ARRAY_PARTITION variable = TempB dim = 1 complete
                FeedB1:
                for(int row = 0; row < Block_Size_K; row++){
                	FeedB2:
                    for(int col = 0; col < Block_Size_M; col++){
                        TempB[row][col] = LocalB[row + loc][it2 + col];
                    }

                }

                Blockmatmul(TempA, TempB, Block_out);

                PS1:
                for(int i = 0; i < Block_Size_M; i++){
                	PS2:
                    for(int j = 0; j < Block_Size_M; j++){
                        LocalC[it1 + i][it2 + j] += Block_out[i][j];
                    }
                }
            }
        }
    }
    //Systolic array finish

    //#pragma HLS ARRAY_PARTITION variable = LocalC dim = 0 complete
     Wout1:
    for(int i = 0; i < Mat_SizeM; i++){
    	Wout2:
        for(int j = 0; j < Mat_SizeM; j++){
            C[i][j] = LocalC[i][j];
        }
    }

}
