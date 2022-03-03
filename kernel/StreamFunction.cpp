#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "../includes/Streamfunction.h"
using namespace std;

//Functions in block mat mul

void LoadA_Block(hls::stream<Block_vec_K> & Arows, Data_t A[Block_Size_M][Block_Size_K]){
    for(int i = 0; i < Block_Size_M; i++){
        #pragma HLS PIPELINE II = 1
        Block_vec_K tempA = Arows.read();
        //stream Arows has "Mat_SizeM" elements,each represent one row in sub A 
        LoadA_Inner:
        for(int j = 0; j < Block_Size_K; j++){
            //Get one row in sub A
            A[i][j] = tempA.vec[j];
        }
    }
}

void LoadB_Block(hls::stream<Block_vec_K> & Bcols, Data_t B[Block_Size_K][Block_Size_N]){
    for(int i = 0; i < Block_Size_N; i++){
        #pragma HLS PIPELINE II = 1
        Block_vec_K tempB = Bcols.read();
        //stream Bcols has "Mat_sizeN" elements, each represent a col in sub_matrix B
        LoadB_Inner:
        for(int j = 0; j < Block_Size_K; j++){
            //Get one col in sub B
            B[j][i] = tempB.vec[j];
        }
    }


}