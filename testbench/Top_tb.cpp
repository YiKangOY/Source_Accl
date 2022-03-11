#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "../includes/KQV.h"
#include "../includes/Softmax.h"
#include "../includes/Top.h"
#include <ctime>
#include <stdlib.h>
using namespace std;

template<int dim1, int dim2, int dim3>
void Matmul_sw(Data_t A[dim1][dim2], Data_t B[dim2][dim3], Data_t out[dim1][dim3]){
    Data_t sum = 0;
    for (int i = 0; i < dim1; i++){
        for(int j = 0; j < dim3; j++){
            sum = 0;
            for(int k = 0; k < dim2; k++){
                sum = sum + A[i][k] * B[k][j];
            }
            out[i][j] = sum;
        }
    }
}
template<int dim1, int dim2>
void Init_mat(Data_t A[dim1][dim2]){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            A[i][j] = (Data_t) (rand() % 10) / 10;
        }
    }
}

template<int dim1, int dim2>
void Init_mat0(Data_t A[dim1][dim2]){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            A[i][j] = 0;
        }
    }
}

template<int dim1, int dim2>
int Compare2mats(Data_t A[dim1][dim2], Data_t B[dim1][dim2]){
    int fail = 0;
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
        	Data_t a = A[i][j];
        	Data_t b = B[i][j];
            if(a != b){
                cout<<"hw result: "<<a<<" sw result: "<<b<<endl;
                fail = 1;
            }
        }
    }
    return fail;
}

int main(){
    int fail = 0;
    Data_t Query[Mat_SizeM][Mat_SizeK];
    Data_t Key[Mat_SizeK][Mat_SizeM];
    Data_t Value[Mat_SizeM][Mat_SizeK];

    Data_t Out_hw[Mat_SizeM][Mat_SizeK];
    Data_t Out_sw[Mat_SizeM][Mat_SizeK];

    
    //Init matrices
    srand((unsigned)time(NULL));
    Init_mat<Mat_SizeM, Mat_SizeK>(Query);
    Init_mat<Mat_SizeK, Mat_SizeM>(Key);
    Init_mat<Mat_SizeM, Mat_SizeK>(Value);
    Init_mat0<Mat_SizeM, Mat_SizeK>(Out_hw);
    Init_mat0<Mat_SizeM, Mat_SizeK>(Out_sw);

    //hw calculate
    Top_Single(Query, Key, Value, Out_hw);

    //sw calculate
    Data_t S[Mat_SizeM][Mat_SizeM];
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, Key, S);
    Data_t Softmax_out[Mat_SizeM][Mat_SizeM];
    Softmax_sw<Mat_SizeM, Mat_SizeM>(S, Softmax_out);
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(Softmax_out, Value, Out_sw);

    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(Out_hw, Out_sw);

    if(!fail){ cout<< "PASS!";}
    return fail;

    


}