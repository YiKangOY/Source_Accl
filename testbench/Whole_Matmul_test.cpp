#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include <stdlib.h>
using namespace std;

void Matmul_sw(Data_t A[Mat_SizeM][Mat_SizeK], Data_t B[Mat_SizeK][Mat_SizeM], Data_t out[Mat_SizeM][Mat_SizeM]){
    Data_t sum = 0;
    for (int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeM; j++){
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
    Data_t A[Mat_SizeM][Mat_SizeK], B[Mat_SizeK][Mat_SizeM];
    Data_t mat_sw[Mat_SizeM][Mat_SizeM], mat_hw[Mat_SizeM][Mat_SizeM];

    Mat_A_t LocalA; Mat_B_t LocalB; Mat_C_t LocalC;

    
InitMatrices:
    for (int i = 0; i< Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            mat_sw[i][j] = 0;
            mat_hw[i][j] = 0;
            for(int k = 0; k < Mat_SizeK; k++){
                A[i][k] = rand() % 10;
                B[k][j] = rand() % 10;
            }
        }
    }


/* WriteToStream:
    hls::stream<Data_t> Astream;
    hls::stream<Data_t> Bstream;
    hls::stream<Data_t> Cstream; */
    
/*     for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeK; j++){
            Astream.write(A[i][j]);
        }
    }

    for(int i = 0; i < Mat_SizeK; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            Bstream.write(B[i][j]);
        }
    } */
Calculate:
    Matmul(A, B, mat_hw);

/* ReadOut:
    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            Cstream.read(mat_hw[i][j]);
        }
    } */

Compare:
    Matmul_sw(A, B, mat_sw);

    for(int i = 0; i < Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            if(mat_hw[i][j] != mat_sw[i][j]) {
                fail = 1;
                cout << "wrong idx, row: "<<i<<" col: "<< j<<endl;
                cout<<"sw result: "<<mat_sw[i][j]<<" , hw result: "<<mat_hw[i][j] << endl;
            }
        }
    }

    if(fail == 1){
        cout<<"Failed"<<endl;
        return 1;
    }
    else{
        cout<<"Passed"<<endl;
    }
    return 0;

}
