#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include "../includes/KQV.h"
#include "../includes/Softmax.h"
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
//Declaration
    Data_t Query[Mat_SizeM][Mat_SizeK];
    //Hardware declare K V and Z
    Data_t K0[Mat_SizeK][Mat_SizeM]; Data_t K1[Mat_SizeK][Mat_SizeM]; Data_t K2[Mat_SizeK][Mat_SizeM]; Data_t K3[Mat_SizeK][Mat_SizeM];
    Data_t K4[Mat_SizeK][Mat_SizeM]; Data_t K5[Mat_SizeK][Mat_SizeM]; Data_t K6[Mat_SizeK][Mat_SizeM]; Data_t K7[Mat_SizeK][Mat_SizeM];
    Data_t V0[Mat_SizeM][Mat_SizeK]; Data_t V1[Mat_SizeM][Mat_SizeK]; Data_t V2[Mat_SizeM][Mat_SizeK]; Data_t V3[Mat_SizeM][Mat_SizeK];
    Data_t V4[Mat_SizeM][Mat_SizeK]; Data_t V5[Mat_SizeM][Mat_SizeK]; Data_t V6[Mat_SizeM][Mat_SizeK]; Data_t V7[Mat_SizeM][Mat_SizeK];
    Data_t Z0[Mat_SizeM][Mat_SizeK]; Data_t Z1[Mat_SizeM][Mat_SizeK]; Data_t Z2[Mat_SizeM][Mat_SizeK]; Data_t Z3[Mat_SizeM][Mat_SizeK]; 
    Data_t Z4[Mat_SizeM][Mat_SizeK]; Data_t Z5[Mat_SizeM][Mat_SizeK]; Data_t Z6[Mat_SizeM][Mat_SizeK]; Data_t Z7[Mat_SizeM][Mat_SizeK];

    //Init Q V Z
    Init_mat<Mat_SizeM, Mat_SizeK>(Query);
    Init_mat<Mat_SizeK, Mat_SizeM>(K0); Init_mat<Mat_SizeK, Mat_SizeM>(K1); Init_mat<Mat_SizeK, Mat_SizeM>(K2); Init_mat<Mat_SizeK, Mat_SizeM>(K3); 
    Init_mat<Mat_SizeK, Mat_SizeM>(K4); Init_mat<Mat_SizeK, Mat_SizeM>(K5); Init_mat<Mat_SizeK, Mat_SizeM>(K6); Init_mat<Mat_SizeK, Mat_SizeM>(K7); 

    Init_mat<Mat_SizeM, Mat_SizeK>(V0); Init_mat<Mat_SizeM, Mat_SizeK>(V1); Init_mat<Mat_SizeM, Mat_SizeK>(V2); Init_mat<Mat_SizeM, Mat_SizeK>(V3);
    Init_mat<Mat_SizeM, Mat_SizeK>(V4); Init_mat<Mat_SizeM, Mat_SizeK>(V5); Init_mat<Mat_SizeM, Mat_SizeK>(V6); Init_mat<Mat_SizeM, Mat_SizeK>(V7);

    Init_mat0<Mat_SizeM, Mat_SizeK>(Z0); Init_mat0<Mat_SizeM, Mat_SizeK>(Z1); Init_mat0<Mat_SizeM, Mat_SizeK>(Z2); Init_mat0<Mat_SizeM, Mat_SizeK>(Z3);
    Init_mat0<Mat_SizeM, Mat_SizeK>(Z4); Init_mat0<Mat_SizeM, Mat_SizeK>(Z5); Init_mat0<Mat_SizeM, Mat_SizeK>(Z6); Init_mat0<Mat_SizeM, Mat_SizeK>(Z7);

    //Call hardware
    KQV_Mul(Query, K0, K1, K2, K3, K4, K5, K6, K7,
            V0, V1, V2, V3, V4, V5, V6, V7,
            Z0, Z1, Z2, Z3, Z4, Z5, Z6, Z7);
    

    //Software Declare intermediate variables
    Data_t KQ_Out0[Mat_SizeM][Mat_SizeM], KQ_Out1[Mat_SizeM][Mat_SizeM], KQ_Out2[Mat_SizeM][Mat_SizeM], KQ_Out3[Mat_SizeM][Mat_SizeM], KQ_Out4[Mat_SizeM][Mat_SizeM],
    KQ_Out5[Mat_SizeM][Mat_SizeM], KQ_Out6[Mat_SizeM][Mat_SizeM], KQ_Out7[Mat_SizeM][Mat_SizeM];
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, K0, KQ_Out0);
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, K1, KQ_Out1);
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, K2, KQ_Out2);
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, K3, KQ_Out3);
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, K4, KQ_Out4);
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, K5, KQ_Out5);
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, K6, KQ_Out6);
    Matmul_sw<Mat_SizeM, Mat_SizeK, Mat_SizeM>(Query, K7, KQ_Out7);

    Data_t SF_Out0[Mat_SizeM][Mat_SizeM], SF_Out1[Mat_SizeM][Mat_SizeM], SF_Out2[Mat_SizeM][Mat_SizeM], SF_Out3[Mat_SizeM][Mat_SizeM], SF_Out4[Mat_SizeM][Mat_SizeM],
    SF_Out5[Mat_SizeM][Mat_SizeM], SF_Out6[Mat_SizeM][Mat_SizeM], SF_Out7[Mat_SizeM][Mat_SizeM];
    Softmax_sw<Mat_SizeM, Mat_SizeM>(KQ_Out0,SF_Out0);
    Softmax_sw<Mat_SizeM, Mat_SizeM>(KQ_Out1,SF_Out1);
    Softmax_sw<Mat_SizeM, Mat_SizeM>(KQ_Out2,SF_Out2);
    Softmax_sw<Mat_SizeM, Mat_SizeM>(KQ_Out3,SF_Out3);
    Softmax_sw<Mat_SizeM, Mat_SizeM>(KQ_Out4,SF_Out4);
    Softmax_sw<Mat_SizeM, Mat_SizeM>(KQ_Out5,SF_Out5);
    Softmax_sw<Mat_SizeM, Mat_SizeM>(KQ_Out6,SF_Out6);
    Softmax_sw<Mat_SizeM, Mat_SizeM>(KQ_Out7,SF_Out7);

    Data_t Z0_sw[Mat_SizeM][Mat_SizeK], Z1_sw[Mat_SizeM][Mat_SizeK], Z2_sw[Mat_SizeM][Mat_SizeK], Z3_sw[Mat_SizeM][Mat_SizeK], Z4_sw[Mat_SizeM][Mat_SizeK],
    Z5_sw[Mat_SizeM][Mat_SizeK], Z6_sw[Mat_SizeM][Mat_SizeK], Z7_sw[Mat_SizeM][Mat_SizeK];

    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(SF_Out0, V0, Z0_sw);
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(SF_Out0, V1, Z1_sw);
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(SF_Out0, V2, Z2_sw);
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(SF_Out0, V3, Z3_sw);
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(SF_Out0, V4, Z4_sw);
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(SF_Out0, V5, Z5_sw);
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(SF_Out0, V6, Z6_sw);
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(SF_Out0, V7, Z7_sw);

    //Compare Hardware and software
    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(Z0, Z0_sw);
    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(Z1, Z1_sw);
    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(Z2, Z2_sw);
    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(Z3, Z3_sw);
    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(Z4, Z4_sw);
    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(Z5, Z5_sw);
    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(Z6, Z6_sw);
    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(Z7, Z7_sw);
    
    if(fail == 0){
        std::cout<<"PASS"<<std::endl;
        return 0;
    }
    std::cout<<"FAILED"<<std::endl;
    return fail;
}
