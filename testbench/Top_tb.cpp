#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "../includes/Softmax.h"
#include "../includes/Top.h"
#include <ctime>
#include <iostream>

template<int dim1, int dim2, int dim3>
void Matmul_sw(float A[dim1][dim2], float B[dim2][dim3], float out[dim1][dim3]){
    float sum = 0;
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
void Init_mat(float A[dim1][dim2]){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            A[i][j] = (float) (rand() % 10) / 10;
        }
    }
}

template<int dim1, int dim2>
void Init_mat0(float A[dim1][dim2]){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            A[i][j] = 0;
        }
    }
}

template<int dim1, int dim2>
int Compare2mats(float A[dim1][dim2], float B[dim1][dim2]){
    int fail = 0;
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
        	float a = A[i][j];
        	float b = B[i][j];
            if( hls::abs(((a - b) / b )) > 0.001 ){
                fail = 1;
            }
            std::cout<<"hw result: "<<a<<" sw result: "<<b<<" "<<"Diff = "<<(a - b)/b<<std::endl;
            std::cout<<"Idx: "<<i<<" "<<j<<std::endl;
            
        }
    }
    return fail;
}

template<int dim1, int dim2>
int Correctness(float A[dim1][dim2], float B[dim1][dim2]){
    int fail = 0;
    for(int i = 0; i < dim1; i++){
        float max1=(float)-9999;
        float max2=(float)-9999;
        int idx1=0;
        int idx2=0;
        for(int j = 0; j < dim2; j++){
            if(A[i][j]>max1){
                max1 = A[i][j];
                idx1 = j;
            }
            if(B[i][j]>max2){
                max2 = B[i][j];
                idx2 = j;
            }
        }
        if(idx1!=idx2){
            fail++;
        }
    }
    return fail;
}

template<int dim1, int dim2>
void Init_1d_mat(float * A){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            A[i*dim2 + j] = static_cast<float> ((rand() % 10) / 10);
        }
    }
}

template<int dim1, int dim2>
void Init_1d_mat_0(float * A){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            A[i*dim2 + j] = static_cast<float>(0) ;
        }
    }
}

template<int dim1, int dim2>
void Mat_1D_to_2D(float *A, float B[dim1][dim2]){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            B[i][j] = A[i * dim2 + j];
        }
    }
}
int One_Test(int idx){
    int fail = 0;
    srand(idx);
    //1d array
    float Q_1d[Mat_SizeM * Mat_SizeK];
    float K_1d[Mat_SizeK * Mat_SizeM];
    float V_1d[Mat_SizeM * Mat_SizeK];
    float O_1d[Mat_SizeM * Mat_SizeK];

    float *P_Q=Q_1d;
    float *P_K=K_1d;
    float *P_V=V_1d;
    float *P_O=O_1d;

    Init_1d_mat<Mat_SizeM, Mat_SizeK>(P_Q);
    Init_1d_mat<Mat_SizeK, Mat_SizeM>(P_K);
    Init_1d_mat<Mat_SizeM, Mat_SizeK>(P_V);
    Init_1d_mat_0<Mat_SizeM, Mat_SizeK>(P_O);

    float Query[Mat_SizeM][Mat_SizeK];
    float Key[Mat_SizeK][Mat_SizeM];
    float Value[Mat_SizeM][Mat_SizeK];

    float Out_hw[Mat_SizeM][Mat_SizeK];
    float Out_sw[Mat_SizeM][Mat_SizeK];

    
    //Init matrices
    Mat_1D_to_2D<Mat_SizeM, Mat_SizeK>(P_Q, Query);
    Mat_1D_to_2D<Mat_SizeK, Mat_SizeM>(P_K, Key);
    Mat_1D_to_2D<Mat_SizeM, Mat_SizeK>(P_V, Value);
    Mat_1D_to_2D<Mat_SizeM, Mat_SizeK>(P_O, Out_hw);
    Mat_1D_to_2D<Mat_SizeM, Mat_SizeK>(P_O, Out_sw);
    

    //hw calculate
    Top(P_Q, P_K, P_V, P_O);
    Mat_1D_to_2D<Mat_SizeM, Mat_SizeK>(P_O, Out_hw);
    //sw calculate
    float S[Mat_SizeM][Mat_SizeM];
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, Key, S);
    float Softmax_out[Mat_SizeM][Mat_SizeM];
    Softmax_sw<float, Mat_SizeM, Mat_SizeM>(S, Softmax_out);
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(Softmax_out, Value, Out_sw);

    fail = Correctness<Mat_SizeM, Mat_SizeK>(Out_hw, Out_sw);

    //if(!fail){ cout<< "PASS!";}
    //else{cout<<fail;}
    return fail;
}

int main(){
   
int all_fail=0;
for(int i = 0; i < 1; i++){
    int temp = 0;
    temp=One_Test(i+123);
    all_fail+=temp;
}
cout<<"wrong rate: "<<all_fail<<endl;

return all_fail;


}
