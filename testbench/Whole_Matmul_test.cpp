#include "../includes/mm_mult.h"
#include "../includes/Matmul.h"
#include <ctime>
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
int Compare2mats(Data_t A[dim1][dim2], Data_t B[dim1][dim2]){
    int fail = 0;
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
        	Data_t a = A[i][j];
        	Data_t b = B[i][j];
            if(abs(((a - b) / b )) > 0.001){
                cout<<"hw result: "<<a<<" sw result: "<<b<<endl;
                fail = 1;
            }
        }
    }
    return fail;
}


int main(){
    int fail = 0;
    Data_t A[Mat_SizeM][Mat_SizeM], B[Mat_SizeM][Mat_SizeK];
    Data_t mat_sw[Mat_SizeM][Mat_SizeK], mat_hw[Mat_SizeM][Mat_SizeK];
    srand((unsigned)time(NULL));
    


    
Init_mat<Mat_SizeM, Mat_SizeM>(A);
Init_mat<Mat_SizeM, Mat_SizeK>(B);
Init_mat0<Mat_SizeM, Mat_SizeK>(mat_sw);
Init_mat0<Mat_SizeM, Mat_SizeK>(mat_hw);



Calculate:
    Wrapper(A, B, mat_hw);



Compare:
    Matmul_sw<Mat_SizeM, Mat_SizeM, Mat_SizeK>(A, B, mat_sw);

    fail = Compare2mats<Mat_SizeM, Mat_SizeK>(mat_hw, mat_sw);

    if(fail == 1){
        cout<<"Failed"<<endl;
        return 1;
    }
    else{
        cout<<"Passed"<<endl;
    }
    return 0;

}
