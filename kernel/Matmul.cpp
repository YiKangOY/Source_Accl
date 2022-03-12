#include "../includes/Matmul.h"
#include "../includes/mm_mult.h"

void Wrapper(Data_t A[Mat_SizeM][Mat_SizeM], Data_t B[Mat_SizeM][Mat_SizeK], Data_t C[Mat_SizeM][Mat_SizeK]){
    Matmul<Mat_SizeM, Mat_SizeM, Mat_SizeK, Block_Size_M, Block_Size_K, Block_Size_N> (A, B, C);
}