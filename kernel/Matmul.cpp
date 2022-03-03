#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"
void Whole_Mat_mul(hls::stream<Data_t> & A, hls::stream<Data_t> & B, hls::stream<Data_t> & C){
    //Local variables
    //#pragma HLS DATAFLOW
    Mat_A_t LocalA_stream; Mat_B_t LocalB_stream; Mat_C_t LocalC_stream;
    Data_t LocalA[Mat_SizeM][Mat_SizeK], LocalB[Mat_SizeK][Mat_SizeN], LocalC[Mat_SizeM][Mat_SizeN];

    Block_mat Block_out;
    hls::stream<Block_vec_K> strm_Arows("strm_Arows");
    hls::stream<Block_vec_K> strm_Bcols("strm_Bcols");
    Block_vec_K strm_Arows_element;
    Block_vec_K strm_Bcols_element;

    //write data in stream to local variables
    
    
    //Local stream variable to matrix
    #pragma HLS ARRAY_PARTITION variable = LocalA dim = 2 complete
    for(int i = 0; i < Mat_SizeM; i++){
    //#pragma HLS PIPELINE II = 1
        for(int j = 0; j < Mat_SizeK; j++){
            LocalA[i][j] = A.read();
        }
    }

    #pragma HLS ARRAY_PARTITION variable = LocalB dim = 1 complete
    for(int i = 0; i < Mat_SizeK; i++){
    //#pragma HLS PIPELINE II = 1
        for(int j = 0; j < Mat_SizeN; j++){
            LocalB[i][j] = B.read();
        }
    }


    //Call systolic array in a tiled shceme
    LoopC_it1:
    for(int it1 = 0; it1 < Mat_SizeM; it1 = it1 + Block_Size_M){
    	LoopC_it2:
        for(int it2 = 0; it2 < Mat_SizeN; it2 = it2 + Block_Size_N){
            //it1 and it2 are used to locate target output in C matrix
        	LoopC_loc:
            for(int loc = 0; loc < Mat_SizeK; loc = loc + Block_Size_K){
                //Blocks in a row (one row has K cols, divide by block_size_k)

                //Feed A to systolic array
            	FeedA_row:
                for(int row = 0; row < Block_Size_M; row++){
                	FeedA_col:
                    for(int col = 0; col < Block_Size_K; col++){
                        strm_Arows_element.vec[col] = LocalA[it1 + row][col + loc];
                    }
                    strm_Arows.write(strm_Arows_element);
                    //Feed a row of block A
                }

                //Feed B to systolic array
                FeedB_row:
                for(int col = 0; col < Block_Size_N; col++){
                	FeedB_col:
                    for(int row = 0; row < Block_Size_K; row++){
                        strm_Bcols_element.vec[row] = LocalB[row + loc][it2 + col];
                    }
                    strm_Bcols.write(strm_Bcols_element);
                    //Feed a col of block b
                }

                Blockmatmul(strm_Arows, strm_Bcols, Block_out);

                PartialSum1:
                for(int i = 0; i < Block_Size_M; i++){
                	PartialSum2:
                    for(int j = 0; j < Block_Size_N; j++){
                        LocalC[it1 + i][it2 + j] += Block_out.mat[i][j];
                    }
                }
            }
        }
    }
    //Systolic array finish

    Writeout1:
    for(int i = 0; i < Mat_SizeM; i++){
    	Writeout2:
        for(int j = 0; j < Mat_SizeN; j++){
            C.write(LocalC[i][j]);
        }
    }



}
