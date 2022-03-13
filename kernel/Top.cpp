#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"
#include "../includes/Softmax.h"
#include "../includes/Top.h"

void Top_Single(Data_t Query[Mat_SizeM][Mat_SizeK], Data_t Key[Mat_SizeK][Mat_SizeM], Data_t Value[Mat_SizeM][Mat_SizeK], Data_t Out[Mat_SizeM][Mat_SizeK]){
    //Copy to local

    Data_t S[Mat_SizeM][Mat_SizeM] = {0};
    Single_QK(Query, Key, S);
    Data_t S_Out[Mat_SizeM][Mat_SizeM];
    Single_Softmax(S, S_Out);
    Single_V(S_Out, Value, Out);
}

void Single_QK(Data_t Q[Mat_SizeM][Mat_SizeK], Data_t K[Mat_SizeK][Mat_SizeM], Data_t S[Mat_SizeM][Mat_SizeM]){
        Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_M>(Q, K, S);
}

void Single_Softmax(Data_t S[Mat_SizeM][Mat_SizeM], Data_t S_Out[Mat_SizeM][Mat_SizeM]){
        Softmax_sw<Mat_SizeM, Mat_SizeM>(S, S_Out);
}

void Single_V(Data_t S_Out[Mat_SizeM][Mat_SizeM], Data_t V[Mat_SizeM][Mat_SizeK], Data_t Out[Mat_SizeM][Mat_SizeK]){
        Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(S_Out, V, Out);
}