## Introduction
This folder contains the sample code for training on compilation.

## Pre-req
If you are running with Mac: 

## Preparation
1. Login to NSCC with NTU account
2. Request an interactive queue of 1h
```bash
$ qsub -I -l select=1:ncpus=12 -P personal -l walltime=01:00:00
```
3. Go to GitHub and search "NTU-HPC-Training-AY18-19"
4. Copy the link and issue the following commands:
```bash
$ git clone git@github.com:StevenShi-23/NTU-HPC-Training-AY18-19.git
$ cd NTU-HPC-Training-AY18-19/1-Compilation
```

## Structure
ex1: compile with g++ and optional flags \
ex2: use macro to compile (only) the desired section of code \
ex3: compile with g++ and Intel respectively, and compare their performance difference.

## Instruction

### ex1:
Try the following:
```bash
# serial hello world
$ g++ hello_world.cpp -o hello
$ ./hello

# parallel hello world with OpenMP
$ gcc -foepnmp omp_hello.c -o omp_hello
$ ./omp_hello
```

### ex2:
Try enabling different macros:
```bash
$ g++ macro_test.cpp -DUSE_MULTI
```
