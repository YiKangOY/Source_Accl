#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "../includes/KQV.h"
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
//Declaration
    Data_t Query[Mat_SizeM][Mat_SizeK];

            Data_t K0[Mat_SizeK][Mat_SizeM]; Data_t K1[Mat_SizeK][Mat_SizeM]; Data_t K2[Mat_SizeK][Mat_SizeM]; Data_t K3[Mat_SizeK][Mat_SizeM];
            Data_t K4[Mat_SizeK][Mat_SizeM]; Data_t K5[Mat_SizeK][Mat_SizeM]; Data_t K6[Mat_SizeK][Mat_SizeM]; Data_t K7[Mat_SizeK][Mat_SizeM];
            Data_t V0[Mat_SizeM][Mat_SizeK]; Data_t V1[Mat_SizeM][Mat_SizeK]; Data_t V2[Mat_SizeM][Mat_SizeK]; Data_t V3[Mat_SizeM][Mat_SizeK];
            Data_t V4[Mat_SizeM][Mat_SizeK]; Data_t V5[Mat_SizeM][Mat_SizeK]; Data_t V6[Mat_SizeM][Mat_SizeK]; Data_t V7[Mat_SizeM][Mat_SizeK];
            Data_t Z0[Mat_SizeM][Mat_SizeK]; Data_t Z1[Mat_SizeM][Mat_SizeK]; Data_t Z2[Mat_SizeM][Mat_SizeK]; Data_t Z3[Mat_SizeM][Mat_SizeK]; 
            Data_t Z4[Mat_SizeM][Mat_SizeK]; Data_t Z5[Mat_SizeM][Mat_SizeK]; Data_t Z6[Mat_SizeM][Mat_SizeK]; Data_t Z7[Mat_SizeM][Mat_SizeK];
}