#ifndef _MM_MULT_H_
#define _MM_MULT_H_
#include <hls_stream.h>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

////It performs M*K x K*M = M * M scheme.
typedef float Data_t;
//Blocksize follows M*K x K*M = M * M scheme
const int Block_Size_M = 4;
const int Block_Size_K = 16;
const int Block_Size_N = 4;



typedef struct {Data_t mat[Block_Size_M][Block_Size_M];} Block_mat;

template<int b1, int b2, int b3>
void Blockmatmul(Data_t A[b1][b2], Data_t B[b2][b3],
                    Data_t ABpartial[b1][b3]){
	//#pragma HLS INLINE off


    #pragma HLS ARRAY_PARTITION variable = A dim = 1 complete
    //Partition in 1 dim so read one row (K elements) a time
    #pragma HLS ARRAY_PARTITION variable = B dim = 2 complete
    //Partition in 2 dim so read one column (K elements) a time
    //#pragma HLS ARRAY_PARTITION variable = ABpartial dim = 0 complete

    Sys1:
    for(int k = 0; k < b2; k++){
        #pragma HLS LOOP_TRIPCOUNT min = b2 max = b2
        Sys2:
        for(int i = 0; i< b1; i++){
            #pragma HLS UNROLL
            Sys3:
            for(int j = 0; j < b3; j++){
                #pragma HLS UNROLL
                Data_t last = (k == 0) ? 0 : ABpartial[i][j];

                Data_t a_val = (i < b1 && k < b2) ? A[i][k] : 0;
                Data_t b_val = (k < b2 && j < b3) ? B[k][j] : 0;
                ABpartial[i][j] = last + a_val * b_val;
            }
        }
    }


}
#endif
