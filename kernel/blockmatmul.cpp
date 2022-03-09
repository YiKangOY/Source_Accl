#include "../includes/mm_mult.h"
/* template<int b1, int b2>
void Blockmatmul(Data_t A[b1][b2], Data_t B[b2][b1],
                    Data_t ABpartial[b1][b1]){
	//#pragma HLS INLINE off


    #pragma HLS ARRAY_PARTITION variable = A dim = 1 complete
    //Partition in 1 dim so read one row (K elements) a time
    #pragma HLS ARRAY_PARTITION variable = B dim = 2 complete
    //Partition in 2 dim so read one column (K elements) a time
    //#pragma HLS ARRAY_PARTITION variable = ABpartial dim = 0 complete

    Sys1:
    for(int k = 0; k < b2; k++){
        #pragma HLS LOOP_TRIPCOUNT min = b2 max = b2
        Sys2:
        for(int i = 0; i< b1; i++){
            #pragma HLS UNROLL
            Sys3:
            for(int j = 0; j < b1; j++){
                #pragma HLS UNROLL
                int last = (k == 0) ? 0 : ABpartial[i][j];

                int a_val = (i < b1 && k < b2) ? A[i][k] : 0;
                int b_val = (k < b2 && j < b1) ? B[k][j] : 0;
                ABpartial[i][j] = last + a_val * b_val;
            }
        }
    }


} */
