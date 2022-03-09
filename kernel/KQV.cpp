#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "../includes/KQV.h"
void KQV_Mul(Data_t Q[Mat_SizeM][Mat_SizeK], 
            Data_t K0[Mat_SizeK][Mat_SizeM], Data_t K1[Mat_SizeK][Mat_SizeM], Data_t K2[Mat_SizeK][Mat_SizeM], Data_t K3[Mat_SizeK][Mat_SizeM],
            Data_t K4[Mat_SizeK][Mat_SizeM], Data_t K5[Mat_SizeK][Mat_SizeM], Data_t K6[Mat_SizeK][Mat_SizeM], Data_t K7[Mat_SizeK][Mat_SizeM],
            Data_t V0[Mat_SizeM][Mat_SizeK], Data_t V1[Mat_SizeM][Mat_SizeK], Data_t V2[Mat_SizeM][Mat_SizeK], Data_t V3[Mat_SizeM][Mat_SizeK],
            Data_t V4[Mat_SizeM][Mat_SizeK], Data_t V5[Mat_SizeM][Mat_SizeK], Data_t V6[Mat_SizeM][Mat_SizeK], Data_t V7[Mat_SizeM][Mat_SizeK],
            Data_t Z0[Mat_SizeM][Mat_SizeK], Data_t Z1[Mat_SizeM][Mat_SizeK], Data_t Z2[Mat_SizeM][Mat_SizeK], Data_t Z3[Mat_SizeM][Mat_SizeK], 
            Data_t Z4[Mat_SizeM][Mat_SizeK], Data_t Z5[Mat_SizeM][Mat_SizeK], Data_t Z6[Mat_SizeM][Mat_SizeK], Data_t Z7[Mat_SizeM][Mat_SizeK])
{
        //K0-K7 actually are K transpose
        Data_t KQ_Out0[Mat_SizeM][Mat_SizeM], KQ_Out1[Mat_SizeM][Mat_SizeM], KQ_Out2[Mat_SizeM][Mat_SizeM], KQ_Out3[Mat_SizeM][Mat_SizeM], KQ_Out4[Mat_SizeM][Mat_SizeM],
        KQ_Out5[Mat_SizeM][Mat_SizeM], KQ_Out6[Mat_SizeM][Mat_SizeM], KQ_Out7[Mat_SizeM][Mat_SizeM];
        //Multiply K and Q
        Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_N>(Q, K0, KQ_Out0);
        Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_N>(Q, K1, KQ_Out1);
        Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_N>(Q, K2, KQ_Out2);
        Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_N>(Q, K3, KQ_Out3);
        Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_N>(Q, K4, KQ_Out4);
        Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_N>(Q, K5, KQ_Out5);
        Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_N>(Q, K6, KQ_Out6);
        Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeM, Block_Size_M, Block_Size_K, Block_Size_N>(Q, K7, KQ_Out7);

        Data_t SF_Out0[Mat_SizeM][Mat_SizeM], SF_Out1[Mat_SizeM][Mat_SizeM], SF_Out2[Mat_SizeM][Mat_SizeM], SF_Out3[Mat_SizeM][Mat_SizeM], SF_Out4[Mat_SizeM][Mat_SizeM],
        SF_Out5[Mat_SizeM][Mat_SizeM], SF_Out6[Mat_SizeM][Mat_SizeM], SF_Out7[Mat_SizeM][Mat_SizeM];
        //Softmax_sw
        Softmax_sw(KQ_Out0,SF_Out0);
        Softmax_sw(KQ_Out1,SF_Out1);
        Softmax_sw(KQ_Out2,SF_Out2);
        Softmax_sw(KQ_Out3,SF_Out3);
        Softmax_sw(KQ_Out4,SF_Out4);
        Softmax_sw(KQ_Out5,SF_Out5);
        Softmax_sw(KQ_Out6,SF_Out6);
        Softmax_sw(KQ_Out7,SF_Out7);

        //Multiply Value

        Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(SF_Out0, V0, Z0);
        Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(SF_Out1, V1, Z1);
        Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(SF_Out2, V2, Z2);
        Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(SF_Out3, V3, Z3);
        Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(SF_Out4, V4, Z4);
        Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(SF_Out5, V5, Z5);
        Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(SF_Out6, V6, Z6);
        Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_M, Block_Size_K>(SF_Out7, V7, Z7);

}