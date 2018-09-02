## Introduction
This folder contains the sample code for training on compilation.

## Preparation
1. Login to NSCC with NTU account
2. Submit an interactive job request of 1h with 12 CPU cores
```bash
# this command may take a while
$ qsub -I -l select=1:ncpus=12 -P personal -l walltime=01:00:00
```
3. Go to GitHub and search "NTU-HPC-Training-AY18-19"
4. Copy the link and issue the following commands:
```bash
# ssh into nscc04, this node got network
$ ssh nscc04-ib0
$ git clone https://github.com/StevenShi-23/NTU-HPC-Training-AY18-19.git
$ cd NTU-HPC-Training-AY18-19/1-Compilation
```

## Structure
ex1: compile with g++ and optional flags \
ex2: use macro to compile (only) the desired section of code \
ex3: compile with g++ and Intel respectively, and compare their performance difference.

## Instruction

### ex1: Hello World!
There are two files under `ex1`. Please explore using  basic flags of GCC/ Intel Compiler.
Try the following:
```bash
# serial hello world
$ g++ hello_world.cpp -o hello
$ ./hello

# parallel hello world with OpenMP. Note: to compile with OpenMP, you need to supply with -fopenmp, 
# otherwise compiler does not know where the functions are defined.
$ gcc -fopenmp omp_hello.c -o omp_hello
$ ./omp_hello
```
By running `omp_hello`, you should be able to get something like the following:
```
Hello World from thread = 18
Hello World from thread = 22
Hello World from thread = 13
Hello World from thread = 14
Hello World from thread = 21
Hello World from thread = 20
Hello World from thread = 4
Hello World from thread = 16
Hello World from thread = 15
Hello World from thread = 8
Hello World from thread = 2
Hello World from thread = 12
Hello World from thread = 7
Hello World from thread = 23
Hello World from thread = 17
Hello World from thread = 9
Hello World from thread = 19
Hello World from thread = 11
Hello World from thread = 10
Hello World from thread = 3
Hello World from thread = 1
Hello World from thread = 5
Hello World from thread = 0
Number of threads = 24
Hello World from thread = 6
```
You can set the number of threads visible to OpenMP by:
```bash
$ export OMP_NUM_THREADS=num_of_threads_you_want
# for instance, export OMP_NUM_THREADS=6
# then rerun the program. 
```

### ex2: Selective compilation with macros
You can pass macro value to compiler, and compiler with use that value when doing preprocessing. 
Try enabling different macros:
```bash
$ g++ macro_test.cpp -o test_default
$ ./test_default

$ g++ macro_test.cpp -DUSE_MULTI -o test_multi
$ ./test_multi

$ g++ macro_test.cpp -DUSE_ADD -o test_add
$ ./test_add


$ g++ macro_test.cpp -DUSE_SUBS -o test_subs
$ ./test_subs
```
Also refer to SC'17 Example : [MrBayes](https://github.com/StevenShi-23/sc17-mrbayes/commit/36411af9ed18430a181f2efc8b54c2a902b3afb4), where we use macro to selectively compile code for AVX2/AVX512.

### ex3: Comparing GCC with Intel compiler
compile with g++ and Intel respectively, and compare their performance difference:
```bash
# loading intel compiler
$ module avail intel
$ module load intelcc
# compile cpp file on intel compiler
$ icc pi.cpp -o inteltest
#compile cpp file on gnu compiler
$ g++ pi.cpp -o gnutest
# run 
$ ./inteltest
$ ./gnutest
```
Output may look like the following:
```
$ ./inteltest
Pi = 3.1415926535897919416
Elapsed CPU time is 5.5099999999999997868

$ ./gnutest
Pi = 3.1415926535897919416
Elapsed CPU time is 7.7000000000000001776
```

