#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "../includes/Softmax.h"
#include "../includes/Top.h"
#include <ctime>
#include <iostream>

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
int Correctness(Data_t A[dim1][dim2], Data_t B[dim1][dim2]){
    int fail = 0;
    for(int i = 0; i < dim1; i++){
        Data_t max1=(Data_t)0;
        Data_t max2=(Data_t)0;
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

int One_Test(int idx){
    int fail = 0;
    Data_t Query[Mat_SizeM][Mat_SizeK];
    Data_t Key[Mat_SizeK][Mat_SizeM];
    Data_t Value[Mat_SizeM][Mat_SizeK];

    Data_t Out_hw[Mat_SizeM][Mat_SizeK];
    Data_t Out_sw[Mat_SizeM][Mat_SizeK];

    
    //Init matrices
    //srand((unsigned)time(NULL));
    srand(idx);
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
    Softmax_sw<Data_t, Mat_SizeM, Mat_SizeM>(S, Softmax_out);
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
    temp=One_Test(i*123);
    all_fail+=temp;
}
cout<<"wrong rate: "<<all_fail<<endl;

return 0;


}