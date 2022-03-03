#ifndef _MM_MULT_H_
#define _MM_MULT_H_
#include <hls_stream.h>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

////It performs M*K x K*N = M * N scheme.
typedef float Data_t;
const int Mat_SizeM = 8;        //num of wordvec being processed one time
const int Mat_SizeK = 512;
const int Mat_SizeN = 64;

//Blocksize follows M*K x K*N = M * N scheme
const int Block_Size_M = 4;
const int Block_Size_K = 64;
const int Block_Size_N = 16;


typedef struct {Data_t vec[Block_Size_M];} Block_vec_M;
typedef struct {Data_t vec[Block_Size_K];} Block_vec_K;
typedef struct {Data_t vec[Block_Size_N];} Block_vec_N;


typedef struct {Data_t mat[Block_Size_M][Block_Size_N];} Block_mat;

void Blockmatmul(hls::stream<Block_vec_K>& Arows, hls::stream<Block_vec_K>& Bcols, 
    Block_mat& ABpartial);
#endif
