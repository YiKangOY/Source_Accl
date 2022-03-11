#include "../includes/KQV.h"
#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"
#include "../includes/Softmax.h"

void Top_Single(Data_t Query[Mat_SizeM][Mat_SizeK], Data_t Key[Mat_SizeK][Mat_SizeM], Data_t Value[Mat_SizeM][Mat_SizeK], Data_t Out[Mat_SizeM][Mat_SizeK]){
    Data_t S[Mat_SizeM][Mat_SizeM];
    Single_QK(Query, Key, S);
    Data_t S_Out[Mat_SizeM][Mat_SizeM];
    Single_Softmax(S, S_Out);
    Single_V(S_Out, Value, Out);
}