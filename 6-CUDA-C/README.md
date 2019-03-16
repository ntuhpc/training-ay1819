
## Comparing the performance of simple vector addition

* Compiler : nvcc
* CPU model : Intel(R) Xeon(R) CPU E5-2686 v4 @ 2.30GHz
* GPU model : Nvidia Tesla V100 (16GB)

### Result

CPU : 0.007701s
GPU : 0.000085s (using 32 blocks and 32 threads per block)

### Speedup

roughly 90x.
