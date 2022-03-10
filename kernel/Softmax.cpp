#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "../includes/Softmax.h"
#include "hls_math.h"


void Softmax_sw(Data_t KQ_Out[Mat_SizeM][Mat_SizeM], Data_t Soft_Out[Mat_SizeM][Mat_SizeM]){
    Data_t ExpSum[Mat_SizeM] = {0};
    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            ExpSum[i] += exp(KQ_Out[i][j]/100);
        }
    }

    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            Soft_Out[i][j] = (exp(KQ_Out[i][j]/100) / ExpSum[i]);
        }
    }

}