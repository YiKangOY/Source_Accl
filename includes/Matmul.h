#ifndef _MATMUL_H
#define _MATMUL_H
#include <hls_stream.h>
#include "mm_mult.h"
using namespace std;

const int Mat_SizeM = 64;        
const int Mat_SizeK = 512;
const int Mat_SizeN = 64;


void Wrapper(Data_t A[Mat_SizeM][Mat_SizeM], Data_t B[Mat_SizeM][Mat_SizeK], Data_t C[Mat_SizeM][Mat_SizeK]);

template<int m1, int m2, int m3, int b1, int b2, int b3>
void Matmul(Data_t A[m1][m2], Data_t B[m2][m3], Data_t C[m1][m3]){

    //Local variables

    Data_t Block_out[b1][b3];


    //Call systolic array in a tiled shceme
    LpC_it1:
    for(int it1 = 0; it1 < m1; it1 = it1 + b1){
        //@todo: add it later, may cause syth slow #pragma HLS UNROLL
        #pragma HLS PIPELINE off
    	LpC_it2:
        for(int it2 = 0; it2 < m3; it2 = it2 + b3){
        //@todo: add it later, may cause syth slow #pragma HLS UNROLL
            //it1 and it2 are used to locate target output in C matrix
            #pragma HLS PIPELINE off
        	LpC_loc:
            for(int loc = 0; loc < m2; loc = loc + b2){
			//#pragma HLS LOOP_FLATTEN off
            #pragma HLS PIPELINE off
            //#pragma HLS UNROLL
                //Feed A to systolic array
                Data_t TempA [b1][b2];      
            	FeedA1:
                for(int col = 0; col < b2; col++){
                	FeedA2:
                    for(int row = 0; row < b1; row++){
                        TempA[row][col] = A[it1 + row][col + loc];
                    }
                }
                //Feed B to systolic array
                Data_t TempB [b2][b3];
                FeedB1:
                for(int row = 0; row < b2; row++){
                	FeedB2:
                    for(int col = 0; col < b3; col++){
                        TempB[row][col] = B[row + loc][it2 + col];
                    }

                }

                Blockmatmul<b1, b2, b3>(TempA, TempB, Block_out);

                PS1:
                for(int i = 0; i < b1; i++){
                	PS2:
                    for(int j = 0; j < b3; j++){
                        C[it1 + i][it2 + j] += Block_out[i][j];
                    }
                }
            }
        }
    }
    //Systolic array finish

} 




#endif
