#include "../includes/mm_mult.h"
#include "../includes/Streamfunction.h"
void Blockmatmul(Data_t A[Block_Size_M][Block_Size_K], Data_t B[Block_Size_K][Block_Size_N],
                    Data_t ABpartial[Block_Size_M][Block_Size_N]){


    #pragma HLS ARRAY_PARTITION variable = A dim = 1 complete
    //Partition in 1 dim so read one row (K elements) a time
    #pragma HLS ARRAY_PARTITION variable = B dim = 2 complete
    //Partition in 2 dim so read one column (K elements) a time
    //#pragma HLS ARRAY_PARTITION variable = ABpartial dim = 0 complete

    Sys1:
    for(int k = 0; k < Block_Size_K; k++){
        #pragma HLS LOOP_TRIPCOUNT min = Block_Size_K max = Block_Size_K
        Sys2:
        for(int i = 0; i< Block_Size_M; i++){
            #pragma HLS UNROLL
            Sys3:
            for(int j = 0; j < Block_Size_N; j++){
                #pragma HLS UNROLL
                int last = (k == 0) ? 0 : ABpartial[i][j];

                int a_val = (i < Block_Size_M && k < Block_Size_K) ? A[i][k] : 0;
                int b_val = (k < Block_Size_K && j < Block_Size_N) ? B[k][j] : 0;
                ABpartial[i][j] = last + a_val * b_val;
            }
        }
    }


}
