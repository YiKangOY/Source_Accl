#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "hls_math.h"

void MergeMat(Data_t SF_Out0[Mat_SizeM][Mat_SizeN], Data_t SF_Out1[Mat_SizeM][Mat_SizeN], Data_t SF_Out2[Mat_SizeM][Mat_SizeN], Data_t SF_Out3[Mat_SizeM][Mat_SizeN],
            Data_t SF_Out4[Mat_SizeM][Mat_SizeN], Data_t SF_Out5[Mat_SizeM][Mat_SizeN], Data_t SF_Out6[Mat_SizeM][Mat_SizeN], Data_t SF_Out7[Mat_SizeM][Mat_SizeN], 
            Data_t Out[Mat_SizeM * 8][Mat_SizeN])
{
    
    for(int i = 0; i< Block_Size_M; i++){
        for(int j = 0; j < Block_Size_N; j++){
            Out[i + Mat_SizeM * 0][j] = SF_Out0[i][j];
        }
    }

    for(int i = 0; i< Block_Size_M; i++){
        for(int j = 0; j < Block_Size_N; j++){
            Out[i + Mat_SizeM][j] = SF_Out0[i][j];
        }
    }

    for(int i = 0; i< Block_Size_M; i++){
        for(int j = 0; j < Block_Size_N; j++){
            Out[i + Mat_SizeM * 2][j] = SF_Out0[i][j];
        }
    }
    
    for(int i = 0; i< Block_Size_M; i++){
        for(int j = 0; j < Block_Size_N; j++){
            Out[i + Mat_SizeM * 3][j] = SF_Out0[i][j];
        }
    }

    for(int i = 0; i< Block_Size_M; i++){
        for(int j = 0; j < Block_Size_N; j++){
            Out[i + Mat_SizeM * 4][j] = SF_Out0[i][j];
        }
    }

    for(int i = 0; i< Block_Size_M; i++){
        for(int j = 0; j < Block_Size_N; j++){
            Out[i + Mat_SizeM * 5][j] = SF_Out0[i][j];
        }
    }

    for(int i = 0; i< Block_Size_M; i++){
        for(int j = 0; j < Block_Size_N; j++){
            Out[i + Mat_SizeM * 6][j] = SF_Out0[i][j];
        }
    }

    for(int i = 0; i< Block_Size_M; i++){
        for(int j = 0; j < Block_Size_N; j++){
            Out[i + Mat_SizeM * 7][j] = SF_Out0[i][j];
        }
    }

    
    
}