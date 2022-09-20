#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define N 10 * 1000
// * 1000

__global__ void vector_add(float *res, float *a, float *b, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < n)
        res[i] = a[i] + b[i];
}

int main()
{
    float *a, *b, *res;
    float *d_a, *d_b, *d_res; 

    // Allocate memory
    a = (float *)malloc(sizeof(float) * N);
    b = (float *)malloc(sizeof(float) * N);
    res = (float *)malloc(sizeof(float) * N);

    // Initialize array
    for (int i = 0; i < N; i++)
    {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    cudaError_t err;
    err = cudaMalloc((void**)&d_a, sizeof(float) * N);
    if(err != cudaSuccess) 
    {
        printf("Error %s:%d: %s\n",__FILE__, __LINE__, cudaGetErrorString(err));
        exit(-1);
    }

    err = cudaMalloc((void**)&d_b, sizeof(float) * N);
    if(err != cudaSuccess) 
    {
        printf("Error %s:%d: %s\n",__FILE__, __LINE__, cudaGetErrorString(err));
        exit(-1);
    }

    err = cudaMalloc((void**)&d_res, sizeof(float) * N);
    if(err != cudaSuccess) 
    {
        printf("Error %s:%d: %s\n",__FILE__, __LINE__, cudaGetErrorString(err));
        exit(-1);
    }

    err = cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
    if(err != cudaSuccess) 
    {
        printf("Error %s:%d: %s\n",__FILE__, __LINE__, cudaGetErrorString(err));
        exit(-1);
    }

    err = cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);
    if(err != cudaSuccess) 
    {
        printf("Error %s:%d: %s\n",__FILE__, __LINE__, cudaGetErrorString(err));
        exit(-1);
    }

    vector_add<<<ceil(N/256.0),256>>>(d_res, d_a, d_b, N);
    
    err = cudaMemcpy(res, d_res, sizeof(float) * N, cudaMemcpyDeviceToHost);
    if(err != cudaSuccess) 
    {
        printf("Error %s:%d: %s\n",__FILE__, __LINE__, cudaGetErrorString(err));
        exit(-1);
    }

    for(int i = 0; i < N; i++){
        if(fabs(res[i] - a[i] - b[i]) > 0.00001) {
            printf("ERROR at %i: fabs(res[%i] (%f) - a[%i](%f) - b[%i](%f)) = %f\n", i, i, res[i], i, a[i], i, b[i], fabs(res[i] - a[i] - b[i]));
            exit(-1);
        }
    }
    printf("OK\n");

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_res);

    // Deallocate host memory
    free(a); 
    free(b); 
    free(res);
}
