#ifndef _MM_MULT_H_
#define _MM_MULT_H_
#include <hls_stream.h>
#include "hls_math.h"
#include <ap_fixed.h>
using namespace std;

////It performs M*K x K*M = M * M scheme.

typedef float Data_t;
//Blocksize follows M*K x K*M = M * M scheme
const int Block_Size_M = 4;
const int Block_Size_K = 4;
const int Block_Size_N = 4;


typedef struct {Data_t mat[Block_Size_M][Block_Size_M];} Block_mat;

template<typename T, int b1, int b2, int b3>
void Blockmatmul(hls::stream<T> A[b1][b2], hls::stream<T> B[b2][b3],
                    hls::stream<T> ABpartial[b1][b3]){

    T LocalA[b1][b2], LocalB[b2][b3], LocalAB[b1][b3];
    #pragma HLS ARRAY_PARTITION variable = LocalA dim = 0 complete
    //Partition in 1 dim so read one row (K elements) a time
    #pragma HLS ARRAY_PARTITION variable = LocalB dim = 0 complete
    //Partition in 2 dim so read one column (K elements) a time
    #pragma HLS ARRAY_PARTITION variable = LocalAB dim = 0 complete
    for(int i = 0; i < b1; i++){
        for(int j = 0; j < b2; j++){
            LocalA[i][j]=A[i][j].read();
        }
    }
    for(int i = 0; i < b2; i++){
        for(int j = 0; j < b3; j++){
            LocalB[i][j]=B[i][j].read();
        }
    }
    Sys1:
    for(int k = 0; k < b2; k++){
        #pragma HLS LOOP_TRIPCOUNT min = b2 max = b2
        #pragma HLS PIPELINE II = 1
        Sys2:
        for(int i = 0; i< b1; i++){
            //#pragma HLS UNROLL
            Sys3:
            for(int j = 0; j < b3; j++){
               // #pragma HLS UNROLL
                T last =  k==0 ? (Data_t) 0 : LocalAB[i][j];

                T a_val = (i < b1 && k < b2) ? LocalA[i][k] : (Data_t)0;
                T b_val = (k < b2 && j < b3) ? LocalB[k][j] : (Data_t)0;

/*                 Data_t a_val = A[i][k];
                Data_t b_val = B[k][j];  */
                LocalAB[i][j] = last + a_val * b_val;

            }
        }
    }
    
    for(int i = 0; i < b1; i++){
        for(int j = 0; j < b3; j++){
            ABpartial[i][j].write(LocalAB[i][j]);
        }
    }


}
#endif
