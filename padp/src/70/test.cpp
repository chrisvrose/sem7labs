#include<iostream>
#include<omp.h>
#include<stdlib.h>
#define VECTOR_SIZE 65536
int main(){
    float* A = (float*)malloc(sizeof(float) * VECTOR_SIZE);
    float* B = (float*)malloc(sizeof(float) * VECTOR_SIZE);
    float* C = (float*)malloc(sizeof(float) * VECTOR_SIZE);
    float alpha = 2.f;
    for (int i = 0; i < VECTOR_SIZE; i++) {
        A[i] = i;
        B[i] = VECTOR_SIZE - i;
        C[i] = 0;
    }

    double t = omp_get_wtime();


    #pragma omp simd
    for(int i=0;i<VECTOR_SIZE;i++){
        C[i] = alpha* A[i] + B[i];
    }
    t = omp_get_wtime()-t;

    for(int i=0;i<VECTOR_SIZE;i++){
        std::cout<<C[i]<<'\n';
    }
    std::cout<<"Time: "<<t<<' '<<'\n';

}