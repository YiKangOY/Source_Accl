#ifndef _DF_UTILS_H
#define _DF_UTILS_H
#include <hls_stream.h>

template<typename T, int dim1, int dim2>
void Rd_From_DF(T Tar[dim1][dim2], hls::stream<T> Src[dim1][dim2]){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            Tar[i][j] = Src[i][j].read();
        }
    }

}


template<typename T, int dim1, int dim2>
void Wr_To_DF(T Src[dim1][dim2], hls::stream<T> Tar[dim1][dim2]){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            Tar[i][j].write(Src[i][j]);
        }
    }
}

template<typename T, int dim1, int dim2, int dim3, int dim4>
void Wr_To_DF2(T Src1[dim1][dim2], hls::stream<T> Tar1[dim1][dim2], T Src2[dim3][dim4], hls::stream<T> Tar2[dim3][dim4]){
    for(int i = 0; i < dim1; i++){
        for(int j = 0; j < dim2; j++){
            Tar1[i][j].write(Src1[i][j]);
        }
    }

    for(int i = 0; i < dim3; i++){
        for(int j = 0; j < dim4; j++){
            Tar2[i][j].write(Src2[i][j]);
        }
    }
}
#endif