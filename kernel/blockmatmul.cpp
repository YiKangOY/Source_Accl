#include "../includes/mm_mult.h"
#include "../includes/Streamfunction.h"
void Blockmatmul(hls::stream<Block_vec_K>& Arows, hls::stream<Block_vec_K>& Bcols,
                    Block_mat& ABpartial){
    #pragma HLS DATAFLOW
    //@todo: have to load A every time?
    Data_t A[Block_Size_M][Block_Size_K];
    #pragma HLS ARRAY_PARTITION variable = A dim = 1 complete
    //Partition in 1 dim so read one row (K elements) a time

    Data_t B[Block_Size_K][Block_Size_N];
    #pragma HLS ARRAY_PARTITION variable = B dim = 2 complete
    //Partition in 2 dim so read one column (K elements) a time

    
    //Read Block_Size_Row rows of A
    LoadA:
    
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

    //Read Block_Size_Row cols of B
    LoadB:
    
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

    Data_t AB[Block_Size_M][Block_Size_N];
    Init1:
    for (int i = 0; i < Block_Size_M; i++){
		#pragma HLS PIPELINE II = 1
    	Init2:
    	for (int j = 0; j < Block_Size_N; j++){
    		AB[i][j]=0;
    	}
    }
    #pragma HLS ARRAY_PARTITION variable = AB dim = 0 complete

    Systolic1:
    for(int k = 0; k < Block_Size_K; k++){
        #pragma HLS LOOP_TRIPCOUNT min = Block_Size_K max = Block_Size_K
        //#pragma HLS PIPELINE II = 1
        Systolic2:
        for(int i = 0; i< Block_Size_M; i++){
            #pragma HLS UNROLL
            Systolic3:
            for(int j = 0; j < Block_Size_N; j++){
                #pragma HLS UNROLL
                int last = (k == 0) ? 0 : AB[i][j];

                int a_val = (i < Block_Size_M && k < Block_Size_K) ? A[i][k] : 0;
                int b_val = (k < Block_Size_K && j < Block_Size_N) ? B[k][j] : 0;
                int result = last + a_val * b_val;

                AB[i][j] = result;
            }
        }
    }

    WriteOut:
        for(int i = 0; i < Block_Size_M; i++){
        #pragma HLS PIPELINE II = 1
        	WriteOut1:
            for(int j = 0; j < Block_Size_N; j++){
                ABpartial.mat[i][j] = AB[i][j];
            }
        }

}
