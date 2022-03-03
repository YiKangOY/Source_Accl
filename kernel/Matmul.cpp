#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"
void Whole_Mat_mul(hls::stream<Mat_A_t> & A, hls::stream<Mat_B_t> & B, hls::stream<Mat_C_t> & C){
    //Local variables
    #pragma HLS DATAFLOW
    Mat_A_t LocalA_stream; Mat_B_t LocalB_stream; Mat_C_t LocalC_stream;
    Data_t LocalA[Mat_SizeM][Mat_SizeK], LocalB[Mat_SizeK][Mat_SizeN], LocalC[Mat_SizeM][Mat_SizeN];
    Block_mat Block_out;
    hls::stream<Block_vec_K> strm_Arows("strm_Arows");
    hls::stream<Block_vec_K> strm_Bcols("strm_Bcols");
    Block_vec_K strm_Arows_element;
    Block_vec_K strm_Bcols_element;

    //write data in stream to local variables
    A.read(LocalA_stream);
    B.read(LocalB_stream);
    
    //Local stream variable to matrix
    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeK; j++){
            LocalA[i][j] = LocalA_stream.mat[i][j];
        }
    }

    for(int i = 0; i < Mat_SizeK; i++){
        for(int j = 0; j < Mat_SizeN; j++){
            LocalB[i][j] = LocalB_stream.mat[i][j];
        }
    }


    //Call systolic array in a tiled shceme
    for(int it1 = 0; it1 < Mat_SizeM; it1 = it1 + Block_Size_M){
        for(int it2 = 0; it2 < Mat_SizeN; it2 = it2 + Block_Size_N){
            //it1 and it2 are used to locate target output in C matrix
            for(int loc = 0; loc < Mat_SizeK; loc = loc + Block_Size_K){
                //Blocks in a row (one row has K cols, divide by block_size_k)

                //Feed A to systolic array
                for(int row = 0; row < Block_Size_M; row++){
                    for(int col = 0; col < Block_Size_K; col++){
                        strm_Arows_element.vec[col] = LocalA[it1 + row][col + loc];
                    }
                    strm_Arows.write(strm_Arows_element);
                    //Feed a row of block A
                }

                //Feed B to systolic array
                for(int col = 0; col < Block_Size_N; col++){
                    for(int row = 0; row < Block_Size_K; row++){
                        strm_Bcols_element.vec[row] = LocalB[row + loc][it2 + col];
                    }
                    strm_Bcols.write(strm_Bcols_element);
                    //Feed a col of block b
                }

                Blockmatmul(strm_Arows, strm_Bcols, Block_out);

                for(int i = 0; i < Block_Size_M; i++){
                    for(int j = 0; j < Block_Size_N; j++){
                        LocalC[it1 + i][it2 + j] += Block_out.mat[i][j];
                    }
                }
            }
        }
    }
    //Systolic array finish

    //Write out result in C
    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeN; j++){
            LocalC_stream.mat[i][j] = LocalC[i][j];
        }
    }
    C.write(LocalC_stream);



}
