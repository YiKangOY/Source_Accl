#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"
#include "../includes/Softmax.h"
#include "../includes/Top.h"

void Top_Single(Data_t Query[Mat_SizeM][Mat_SizeK], Data_t Key[Mat_SizeK][Mat_SizeM], Data_t Value[Mat_SizeM][Mat_SizeK], Data_t Out[Mat_SizeM][Mat_SizeK]){
        //Copy to local
        #pragma HLS INTERFACE s_axilite port=return bundle=for_control
        #pragma HLS INTERFACE m_axi port=Query offset=slave bundle=gmem0
        #pragma HLS INTERFACE m_axi port=Key offset=slave bundle=gmem1
        #pragma HLS INTERFACE m_axi port=Value offset=slave bundle=gmem2
        #pragma HLS INTERFACE m_axi port=Out offset=slave bundle=gmem3
        Data_t LocalQ[Mat_SizeM][Mat_SizeK], LocalK[Mat_SizeK][Mat_SizeM], LocalV[Mat_SizeM][Mat_SizeK];
        Data_t LocalOut[Mat_SizeM][Mat_SizeK] = {0};
        for(int i = 0; i < Mat_SizeM; i++){
                for(int j = 0; j < Mat_SizeK; j++){
                        LocalQ[i][j] = Query[i][j];
                }
        }

        for(int i = 0; i < Mat_SizeK; i++){
                for(int j = 0; j < Mat_SizeM; j++){
                        LocalK[i][j] = Key[i][j];
                }
        }
        
        for(int i = 0; i < Mat_SizeM; i++){
                for(int j = 0; j < Mat_SizeK; j++){
                        LocalV[i][j] = Value[i][j];
                }
        }

        Data_t S[Mat_SizeM][Mat_SizeM] = {0};
        Single_QK(LocalQ, LocalK, S);
        Data_t S_Out[Mat_SizeM][Mat_SizeM];
        Single_Softmax(S, S_Out);
        Single_V(S_Out, LocalV, LocalOut);

        for(int i = 0; i < Mat_SizeM; i++){
                for(int j = 0; j < Mat_SizeK; j++){
                        Out[i][j] = LocalOut[i][j];
                }
        }
}

void Single_QK(Data_t Q[Mat_SizeM][Mat_SizeK], Data_t K[Mat_SizeK][Mat_SizeM], Data_t S[Mat_SizeM][Mat_SizeM]){
        Matmul<Data_t, Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_M>(Q, K, S);
}

void Single_Softmax(Data_t S[Mat_SizeM][Mat_SizeM], Data_t S_Out[Mat_SizeM][Mat_SizeM]){
        Softmax_sw<Data_t, Mat_SizeM, Mat_SizeM>(S, S_Out);
}

void Single_V(Data_t S_Out[Mat_SizeM][Mat_SizeM], Data_t V[Mat_SizeM][Mat_SizeK], Data_t Out[Mat_SizeM][Mat_SizeK]){
        Matmul<Data_t, Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(S_Out, V, Out);
}