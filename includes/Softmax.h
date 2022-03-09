#ifndef _SOFTMAX_H
#define _SOFTMAX_H
#include "mm_mult.h"
#include "Matmul.h"

void Softmax_sw(Data_t KQ_Out[Mat_SizeM][Mat_SizeM], Data_t Soft_Out[Mat_SizeM][Mat_SizeM]);

#endif