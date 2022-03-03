#ifndef _STREAMFUNCTION_H
#define _STREAMFUNCTION_H
#include <hls_stream.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "mm_mult.h"
using namespace std;

void LoadA_Block(hls::stream<Block_vec_K> & Arows, Data_t A[Block_Size_M][Block_Size_K]);
void LoadB_Block(hls::stream<Block_vec_K> & Bcols, Data_t B[Block_Size_K][Block_Size_N]);
#endif