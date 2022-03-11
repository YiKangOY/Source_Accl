#ifndef _TOP_H
#define _TOP_H
#include <hls_stream.h>
#include "mm_mult.h"
#include "Matmul.h"
#include "Softmax.h"
#include "KQV.h"

void Top_Single(Data_t Query[Mat_SizeM][Mat_SizeK], Data_t Key[Mat_SizeK][Mat_SizeM], Data_t Value[Mat_SizeM][Mat_SizeK], Data_t Out[Mat_SizeM][Mat_SizeK]);

#endif