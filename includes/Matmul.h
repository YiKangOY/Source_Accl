#ifndef _MATMUL_H
#define _MATMUL_H
#include <hls_stream.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "mm_mult.h"
using namespace std;




typedef struct {Data_t vec[Mat_SizeM];} Mat_vec_Row;
typedef struct {Data_t vec[Mat_SizeK];} Mat_vec_Col;


typedef struct {Data_t mat[Mat_SizeM][Mat_SizeK];} Mat_A_t;
typedef struct {Data_t mat[Mat_SizeK][Mat_SizeN];} Mat_B_t;
typedef struct {Data_t mat[Mat_SizeM][Mat_SizeN];} Mat_C_t;

void Whole_Mat_mul(hls::stream<Data_t> & A, hls::stream<Data_t> & B, hls::stream<Data_t> & C);


#endif