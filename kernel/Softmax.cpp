#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "hls_math.h"

void Softmax_sw(Data_t KQ_Out[Mat_SizeM][Mat_SizeM], Data_t Soft_Out[Mat_SizeM][Mat_SizeM]){
    Data_t ExpSum[Block_Size_M];
    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeK; j++){
            ExpSum[i] += exp(KQ_Out[i][j]);
        }
    }

    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeK; j++){
            Soft_Out[i][j] = (exp(KQ_Out[i][j]) / ExpSum[i]) / 8;
        }
    }

}