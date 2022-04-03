#ifndef _SOFTMAX_H
#define _SOFTMAX_H
#include "mm_mult.h"
#include "Matmul.h"
#include "hls_math.h"

//Perform softmax for each row in matrix
template<typename T, int dim1, int dim2>
void Softmax_sw(T KQ_Out[dim1][dim2], T Soft_Out[dim1][dim2]){

    T ExpSum[dim1] = {0};
    T Max_in_row[dim1] = {0};
    T Exp_Res[dim1][dim2];

SF_Findmax:
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            if(KQ_Out[i][j] > Max_in_row[i]){
                Max_in_row[i] = KQ_Out[i][j];
            }
        }
    }

SF_Reduce:
    for(int i = 0; i < dim1; i++){
        T temp_max = Max_in_row[i];
        for(int j = 0; j < dim2; j++){
            KQ_Out[i][j] -= temp_max;
        }
    }

EXP_Sum:
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            ExpSum[i]+=hls::exp(KQ_Out[i][j]);
        }
    }
Exp_Out:
    for(int i = 0; i < dim1; i++){
        T temp = ExpSum[i];
        for(int j = 0; j < dim2; j++){
            Soft_Out[i][j] =hls::exp(KQ_Out[i][j]) / temp;
        }
    }


}



#endif