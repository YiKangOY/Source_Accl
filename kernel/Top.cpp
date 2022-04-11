#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"
#include "../includes/Softmax.h"
#include "../includes/Top.h"

void Top(float *Q, float *K, float *V, float *Result){
        #pragma HLS INTERFACE s_axilite register port=return 
        #pragma HLS INTERFACE m_axi port=Q offset=slave bundle=Q depth = 32768
        #pragma HLS INTERFACE m_axi port=K offset=slave bundle=K depth = 32768
        #pragma HLS INTERFACE m_axi port=V offset=slave bundle=V depth = 32768
        #pragma HLS INTERFACE m_axi port=Result offset=slave bundle=RES depth = 32768


	Data_t LocalQ[Mat_SizeM][Mat_SizeK], LocalK[Mat_SizeK][Mat_SizeM], LocalV[Mat_SizeM][Mat_SizeK];
        Data_t LocalOut[Mat_SizeM][Mat_SizeK] = {0};
        for(int i = 0; i < Mat_SizeM; i++){
                for(int j = 0; j < Mat_SizeK; j++){
                        LocalQ[i][j] = static_cast<half> (Q[i * Mat_SizeK + j]);
                }
        }

        for(int i = 0; i < Mat_SizeK; i++){
                for(int j = 0; j < Mat_SizeM; j++){
                        LocalK[i][j] = static_cast<half> (K[i * Mat_SizeM + j]);
                }
        }
        
        for(int i = 0; i < Mat_SizeM; i++){
                for(int j = 0; j < Mat_SizeK; j++){
                        LocalV[i][j] = static_cast<half> (V[i * Mat_SizeK + j]);
                }
        }

        Data_t S[Mat_SizeM][Mat_SizeM] = {0};
        Single_QK(LocalQ, LocalK, S);
        Data_t S_Out[Mat_SizeM][Mat_SizeM];
        Single_Softmax(S, S_Out);
        Single_V(S_Out, LocalV, LocalOut);

        for(int i = 0; i < Mat_SizeM; i++){
                for(int j = 0; j < Mat_SizeK; j++){
                        Result[i * Mat_SizeK + j] =static_cast<float> (LocalOut[i][j]);
                }
        }
}

void Single_QK(Data_t Q[Mat_SizeM][Mat_SizeK], Data_t K[Mat_SizeK][Mat_SizeM], Data_t S[Mat_SizeM][Mat_SizeM]){
        Matmul<Data_t, Mat_SizeM, Mat_SizeK, Mat_SizeM, 4, 4, 4>(Q, K, S);
}

void Single_Softmax(Data_t S[Mat_SizeM][Mat_SizeM], Data_t S_Out[Mat_SizeM][Mat_SizeM]){
        Softmax_sw<Data_t, Mat_SizeM, Mat_SizeM>(S, S_Out); 
}

void Single_V(Data_t S_Out[Mat_SizeM][Mat_SizeM], Data_t V[Mat_SizeM][Mat_SizeK], Data_t Out[Mat_SizeM][Mat_SizeK]){
        Matmul<Data_t, Mat_SizeM, Mat_SizeM, Mat_SizeK, 4, 4, 4>(S_Out, V, Out);
}
