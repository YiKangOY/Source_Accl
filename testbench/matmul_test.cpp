#include "../includes/mm_mult.h"
#include <stdlib.h>
using namespace std;

void Matmul_sw(Data_t A[Mat_SizeM][Mat_SizeK], Data_t B[Mat_SizeK][Mat_SizeN], Data_t out[Mat_SizeM][Mat_SizeN]){
    Data_t sum = 0;
    for (int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeN; j++){
            sum = 0;
            for(int k = 0; k < Mat_SizeK; k++){
                sum = sum + A[i][k] * B[k][j];
            }
            out[i][j] = sum;
        }
    }
}

int main(){
    int fail = 0;
    hls::stream<Block_vec_K> strm_mat1("strm_mat1");
    hls::stream<Block_vec_K> strm_mat2("strm_mat2");
    Block_vec_K strm_mat1_element;
    Block_vec_K strm_mat2_element;
    Block_mat block_out;

    Data_t A[Mat_SizeM][Mat_SizeK], B[Mat_SizeK][Mat_SizeN];
    Data_t mat_sw[Mat_SizeM][Mat_SizeN], mat_hw[Mat_SizeM][Mat_SizeN];
    //cout<<Mat_SizeM<<"    "<<Block_Size_Row<<endl;
InitMatrices:
    for (int i = 0; i< Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeN; j++){
            mat_sw[i][j] = 0;
            mat_hw[i][j] = 0;
            for(int k = 0; k < Mat_SizeK; k++){
                A[i][k] = rand() % 10;
                B[k][j] = rand() % 10;
            }
        }
    }
    for (int it1 = 0; it1 < Mat_SizeM; it1 = it1 + Block_Size_M){
        for(int it2 = 0; it2< Mat_SizeN; it2 = it2 + Block_Size_N){
            for(int loc = 0; loc < Mat_SizeK; loc = loc + Block_Size_K){

                //readA
                for(int row = 0; row <  Block_Size_M; row = row + 1){
                    for(int col = 0; col <  Block_Size_K; col = col + 1){
                        strm_mat1_element.vec[col] = A[it1 + row][col + loc];
                    }
                        strm_mat1.write(strm_mat1_element);
                }

                //readB
                for(int col = 0; col <  Block_Size_N; col = col + 1){
                    for(int row = 0; row <  Block_Size_K; row = row + 1){
                        strm_mat2_element.vec[row] = B[row + loc][it2 + col];
                    }
                        strm_mat2.write(strm_mat2_element);
                }
                

                Blockmatmul(strm_mat1, strm_mat2, block_out);


                for(int i = 0; i<Block_Size_M; i++){
                    for(int j = 0; j<Block_Size_N; j++){
                        mat_hw[it1+i][it2+j] += block_out.mat[i][j];
                    }   
                }
            }


        }
    }
/*	
	for (int i = 0; i < Mat_SizeM; i++){
		for (int j = 0; j < Mat_SizeN; j++){
			cout << mat_hw[i][j] << " ";
		}
		cout << endl;
	}
    cout<<endl;
*/
    Matmul_sw(A, B, mat_sw);
/*
	for (int i = 0; i < Mat_SizeM; i++){
		for (int j = 0; j < Mat_SizeN; j++){
			cout << mat_sw[i][j] << " ";
		}
		cout << endl;
	}
*/

    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeN; j++){
            if(mat_hw[i][j] != mat_sw[i][j]) {
                fail = 1;
                cout << "wrong idx, row: "<<i<<" col: "<< j<<endl;
                cout<<"sw result: "<<mat_sw[i][j]<<" , hw result: "<<mat_hw[i][j] << endl;
            }
        }
    }
    if(fail == 1){
        cout<<"Failed"<<endl;
        return -1;
    }
    else{
        cout<<"Passed"<<endl;
    }
    return 0;
}