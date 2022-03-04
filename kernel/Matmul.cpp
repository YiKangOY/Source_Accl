#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"
void Matmul(hls::stream<Data_t> & A, hls::stream<Data_t> & B, hls::stream<Data_t> & C){
    //Local variables
    Mat_A_t LocalA_stream; Mat_B_t LocalB_stream; Mat_C_t LocalC_stream;
    Data_t LocalA[Mat_SizeM][Mat_SizeK], LocalB[Mat_SizeK][Mat_SizeN], LocalC[Mat_SizeM][Mat_SizeN];

    Data_t Block_out[Block_Size_M][Block_Size_N];

    //Local stream variable to matrix
    #pragma HLS ARRAY_PARTITION variable = LocalA dim = 2 complete
    for(int i = 0; i < Mat_SizeM; i++){
    //#pragma HLS PIPELINE II = 1
        for(int j = 0; j < Mat_SizeK; j++){
            LocalA[i][j] = A.read();
        }
    }

    #pragma HLS ARRAY_PARTITION variable = LocalB dim = 2 complete
    for(int i = 0; i < Mat_SizeK; i++){
    //#pragma HLS PIPELINE II = 1
        for(int j = 0; j < Mat_SizeN; j++){
            LocalB[i][j] = B.read();
        }
    }


    //Call systolic array in a tiled shceme
    LpC_it1:
    for(int it1 = 0; it1 < Mat_SizeM; it1 = it1 + Block_Size_M){
        #pragma HLS PIPELINE off
    	LpC_it2:
        for(int it2 = 0; it2 < Mat_SizeN; it2 = it2 + Block_Size_N){
            //it1 and it2 are used to locate target output in C matrix
            #pragma HLS PIPELINE off
        	LpC_loc:
            for(int loc = 0; loc < Mat_SizeK; loc = loc + Block_Size_K){
			#pragma HLS LOOP_FLATTEN off
            #pragma HLS PIPELINE off
			
                //Blocks in a row (one row has K cols, divide by block_size_k)

                //Feed A to systolic array
                Data_t TempA [Block_Size_M][Block_Size_K];
                #pragma HLS ARRAY_PARTITION variable = TempA dim = 2 complete
            	FeedA1:
                for(int row = 0; row < Block_Size_M; row++){
                	FeedA2:
                    for(int col = 0; col < Block_Size_K; col++){
                        TempA[row][col] = LocalA[it1 + row][col + loc];
                    }
                }

                //Feed B to systolic array
                Data_t TempB [Block_Size_K][Block_Size_N];
                #pragma HLS ARRAY_PARTITION variable = TempB dim = 1 complete
                FeedB1:
                for(int row = 0; row < Block_Size_K; row++){
                	FeedB2:
                    for(int col = 0; col < Block_Size_N; col++){
                        TempB[row][col] = LocalB[row + loc][it2 + col];
                    }

                }

                Blockmatmul(TempA, TempB, Block_out);

                PS1:
                for(int i = 0; i < Block_Size_M; i++){
                	PS2:
                    for(int j = 0; j < Block_Size_N; j++){
                        LocalC[it1 + i][it2 + j] += Block_out[i][j];
                    }
                }
            }
        }
    }
    //Systolic array finish

    #pragma HLS ARRAY_PARTITION variable = LocalC dim = 0 complete
    Wout1:
    for(int i = 0; i < Mat_SizeM; i++){
    	Wout2:
        for(int j = 0; j < Mat_SizeN; j++){
            C.write(LocalC[i][j]);
        }
    }



}
