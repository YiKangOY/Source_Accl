#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"

void Wrapper(Data_t A[Mat_SizeM][Mat_SizeK], Data_t B[Mat_SizeK][Mat_SizeM], Data_t C[Mat_SizeM][Mat_SizeM]){
    Matmul<Mat_SizeM, Mat_SizeK, Mat_SizeN, Block_Size_M, Block_Size_K, Block_Size_N> (A, B, C);
}