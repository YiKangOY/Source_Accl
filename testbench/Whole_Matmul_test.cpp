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

    


    
InitMatrices:
    for (int i = 0; i< Mat_SizeM; i++){
        for(int j = 0; j < Mat_SizeM; j++){
            mat_sw[i][j] = 0;
            mat_hw[i][j] = 0;
            for(int k = 0; k < Mat_SizeK; k++){
                A[i][k] = (Data_t)(rand() % 3);
                B[k][j] = (Data_t)(rand() % 3);
            }
        }
    }



Calculate:
    Wrapper(A, B, mat_hw);



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
