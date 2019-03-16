#include <stdio.h>
#include <time.h>
#include <assert.h>

inline cudaError_t checkCuda(cudaError_t result)
{
  if (result != cudaSuccess) {
    fprintf(stderr, "CUDA Runtime Error: %s\n", cudaGetErrorString(result));
    assert(result == cudaSuccess);
  }
  return result;
}


void initWith(float num, float *a, int N)
{
  for(int i = 0; i < N; ++i)
  {
    a[i] = num;
  }
}

__global__
void addVectorsInto(float *result, float *a, float *b, int N)
{
  int i = threadIdx.x + blockDim.x * blockIdx.x;
  int gridStride = gridDim.x * blockDim.x;
  
  for(i; i < N; i+=gridStride)
  {
    result[i] = a[i] + b[i];
  }
}

void checkElementsAre(float target, float *array, int N)
{
  for(int i = 0; i < N; i++)
  {
    if(array[i] != target)
    {
      printf("FAIL: array[%d] - %0.0f does not equal %0.0f\n", i, array[i], target);
      exit(1);
    }
  }
  printf("SUCCESS! All values added correctly.\n");
}

int main()
{
  const int N = 2<<20;
  size_t size = N * sizeof(float);

  float *a;
  float *b;
  float *c;

  checkCuda(cudaMallocManaged(&a,size));
  checkCuda(cudaMallocManaged(&b,size));
  checkCuda(cudaMallocManaged(&c,size));

  initWith(3, a, N);
  initWith(4, b, N);
  initWith(0, c, N);
  
  const int threads_per_block = 32;
  const int num_blocks = 256;
  
  clock_t begin = clock();
  addVectorsInto<<<num_blocks, threads_per_block>>>(c, a, b, N);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Elapsed time for addVectorsInto on GPU is %lf \n", time_spent);
  
  checkCuda(cudaDeviceSynchronize());
  checkElementsAre(7, c, N);

  cudaFree(a);
  cudaFree(b);
  cudaFree(c);
}
