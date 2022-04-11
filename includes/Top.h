#ifndef _TOP_H
#define _TOP_H
#include <hls_stream.h>
#include "mm_mult.h"
#include "Matmul.h"
#include "Softmax.h"


void Top(float *Q, float *K, float *V, float *Result);

void Single_QK(Data_t Q[Mat_SizeM][Mat_SizeK], Data_t K[Mat_SizeK][Mat_SizeM], Data_t S[Mat_SizeM][Mat_SizeM]);

void Single_Softmax(Data_t S[Mat_SizeM][Mat_SizeM], Data_t S_Out[Mat_SizeM][Mat_SizeM]);

void Single_V(Data_t S_Out[Mat_SizeM][Mat_SizeM], Data_t V[Mat_SizeM][Mat_SizeK], Data_t Out[Mat_SizeM][Mat_SizeK]);

#endif