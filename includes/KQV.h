#ifndef _KQV_H
#define _KQV_H
#include <hls_stream.h>
#include "mm_mult.h"
#include "Matmul.h"
using namespace std;

void KQ_Mul(Data_t Q[Mat_SizeM][Mat_SizeK], 
            Data_t K0[Mat_SizeK][Mat_SizeM], Data_t K1[Mat_SizeK][Mat_SizeM], Data_t K2[Mat_SizeK][Mat_SizeM], Data_t K3[Mat_SizeK][Mat_SizeM],
            Data_t K4[Mat_SizeK][Mat_SizeM], Data_t K5[Mat_SizeK][Mat_SizeM], Data_t K6[Mat_SizeK][Mat_SizeM], Data_t K7[Mat_SizeK][Mat_SizeM],
            Data_t V0[Mat_SizeM][Mat_SizeK], Data_t V1[Mat_SizeM][Mat_SizeK], Data_t V2[Mat_SizeM][Mat_SizeK], Data_t V3[Mat_SizeM][Mat_SizeK],
            Data_t V4[Mat_SizeM][Mat_SizeK], Data_t V5[Mat_SizeM][Mat_SizeK], Data_t V6[Mat_SizeM][Mat_SizeK], Data_t V7[Mat_SizeM][Mat_SizeK]);

void Softmax(Data_t KQ_Out[Mat_SizeM][Mat_SizeM], Data_t Soft_Out[Mat_SizeM][Mat_SizeM]);

void MergeMat(Data_t SF_Out0[Mat_SizeM][Mat_SizeM], Data_t SF_Out1[Mat_SizeM][Mat_SizeM], Data_t SF_Out2[Mat_SizeM][Mat_SizeM], Data_t SF_Out3[Mat_SizeM][Mat_SizeM],
            Data_t SF_Out4[Mat_SizeM][Mat_SizeM], Data_t SF_Out5[Mat_SizeM][Mat_SizeM], Data_t SF_Out6[Mat_SizeM][Mat_SizeM], Data_t SF_Out7[Mat_SizeM][Mat_SizeM], 
            Data_t Out[Mat_SizeM * 8][Mat_SizeM]);

#endif