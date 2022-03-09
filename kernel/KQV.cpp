#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "../includes/KQV.h"
void KQ_Mul(Data_t Q[Mat_SizeM][Mat_SizeK], 
            Data_t K0[Mat_SizeK][Mat_SizeM], Data_t K1[Mat_SizeK][Mat_SizeM], Data_t K2[Mat_SizeK][Mat_SizeM], Data_t K3[Mat_SizeK][Mat_SizeM],
            Data_t K4[Mat_SizeK][Mat_SizeM], Data_t K5[Mat_SizeK][Mat_SizeM], Data_t K6[Mat_SizeK][Mat_SizeM], Data_t K7[Mat_SizeK][Mat_SizeM],
            Data_t V0[Mat_SizeM][Mat_SizeK], Data_t V1[Mat_SizeM][Mat_SizeK], Data_t V2[Mat_SizeM][Mat_SizeK], Data_t V3[Mat_SizeM][Mat_SizeK],
            Data_t V4[Mat_SizeM][Mat_SizeK], Data_t V5[Mat_SizeM][Mat_SizeK], Data_t V6[Mat_SizeM][Mat_SizeK], Data_t V7[Mat_SizeM][Mat_SizeK])
{
    //K0-K7 actually are K transpose
    Data_t KQ_Out0[Mat_SizeM][Mat_SizeM], KQ_Out1[Mat_SizeM][Mat_SizeM], KQ_Out2[Mat_SizeM][Mat_SizeM], KQ_Out3[Mat_SizeM][Mat_SizeM], KQ_Out4[Mat_SizeM][Mat_SizeM],
            KQ_Out5[Mat_SizeM][Mat_SizeM], KQ_Out6[Mat_SizeM][Mat_SizeM], KQ_Out7[Mat_SizeM][Mat_SizeM];
    //Multiply K and Q
    Matmul(Q, K0, KQ_Out0);
    Matmul(Q, K1, KQ_Out1);
    Matmul(Q, K2, KQ_Out2);
    Matmul(Q, K3, KQ_Out3);
    Matmul(Q, K4, KQ_Out4);
    Matmul(Q, K5, KQ_Out5);
    Matmul(Q, K6, KQ_Out6);
    Matmul(Q, K7, KQ_Out7);

    Data_t SF_Out0[Mat_SizeM][Mat_SizeM], SF_Out1[Mat_SizeM][Mat_SizeM], SF_Out2[Mat_SizeM][Mat_SizeM], SF_Out3[Mat_SizeM][Mat_SizeM], SF_Out4[Mat_SizeM][Mat_SizeM],
            SF_Out5[Mat_SizeM][Mat_SizeM], SF_Out6[Mat_SizeM][Mat_SizeM], SF_Out7[Mat_SizeM][Mat_SizeM];
    //Softmax
    Softmax(KQ_Out0,SF_Out0);
    Softmax(KQ_Out1,SF_Out1);
    Softmax(KQ_Out2,SF_Out2);
    Softmax(KQ_Out3,SF_Out3);
    Softmax(KQ_Out4,SF_Out4);
    Softmax(KQ_Out5,SF_Out5);
    Softmax(KQ_Out6,SF_Out6);
    Softmax(KQ_Out7,SF_Out7);

    //Multiply Value
        

    //Merge data
    Data_t Out[Mat_SizeM * 8][Mat_SizeM];
    MergeMat(SF_Out0, SF_Out1, SF_Out2, SF_Out3, SF_Out4, SF_Out5, SF_Out6, SF_Out7, Out);



}