#ifndef _MM_MULT_H_
#define _MM_MULT_H_
#include <hls_stream.h>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

////It performs M*K x K*N = M * N scheme.
typedef int16_t Data_t;
const int Mat_SizeM = 24;        //num of wordvec being processed one time
const int Mat_SizeK = 512;


//Blocksize follows M*K x K*N = M * N scheme
const int Block_Size_M = 4;
const int Block_Size_K = 16;



typedef struct {Data_t vec[Block_Size_M];} Block_vec_M;
typedef struct {Data_t vec[Block_Size_K];} Block_vec_K;
typedef struct {Data_t vec[Block_Size_M];} Block_vec_N;


typedef struct {Data_t mat[Block_Size_M][Block_Size_M];} Block_mat;

void Blockmatmul(Data_t A[Block_Size_M][Block_Size_K], Data_t B[Block_Size_K][Block_Size_M],
                    Data_t ABpartial[Block_Size_M][Block_Size_M]);
#endif
