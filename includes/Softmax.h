#ifndef _SOFTMAX_H
#define _SOFTMAX_H
#include "mm_mult.h"
#include "Matmul.h"
#include "hls_math.h"

//Perform softmax for each row in matrix
template<int dim1, int dim2>
void Softmax_sw(Data_t KQ_Out[dim1][dim2], Data_t Soft_Out[dim1][dim2]){
    Data_t ExpSum[dim1] = {0};
    Data_t Exp_Res[dim1][dim2];
    #pragma HLS ARRAY_PARTITION variable = KQ_Out dim = 2 complete
    #pragma HLS ARRAY_PARTITION variable = ExpSum dim = 1 complete
    #pragma HLS ARRAY_PARTITION variable = Soft_Out dim = 2 complete
    #pragma HLS ARRAY_PARTITION variable = Exp_Res dim = 2 complete
SF_MAX1:
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            Exp_Res[i][j] = exp(KQ_Out[i][j]/100);
        }
    }

SF_MAX2:
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            ExpSum[i] += Exp_Res[i][j];
        }
    }

SF_MAX3:
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            Soft_Out[i][j] = (exp(KQ_Out[i][j]/100) / ExpSum[i]);
        }
    }
}
#endif