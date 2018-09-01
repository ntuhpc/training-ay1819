# Why OpenMP

- Syntax is easy yet effective

## Existing native parallel solutions in C and Fortran

- Unified Parallel C (UPC) in C

- Fortran:

  - CoArray Fortran

  - DO CONCURRENT from Fortran 2008

  - None of them becomes mainstream

# OpenMP programming model

a. Based on threads instead of cores (so hyperthreading counts)

b. Each thread has it own copy of code and run in private memory

c. Each OpenMP thread is managed by the OMP runtime system

i. Runtime decide the best way to run, in contrast to MPI

d. Thread safe: a function execute correctly even then executed concurrently by multiple threads

## How to use

a. Compiler Directives

b. Environmental Variables

c. Runtime Library Routines (e.g.: call runtime routine to determine the thread ID)

## Feature set

1\. Parallel Construct

2\. Work-sharing constructs (loop, section, single, workshare (fortran only))

3\. data-sharing, no wait, schedule clauses

4\. Synchronization construct (barrier, critical, atomic, locks, master (for sync.))

\## How to compile

```shell
icc -qopenmp omp_hello.c -o hello
gcc -fopenmp omp_hello.c -o hello
pgcc -mp omp_hello.c -o hello
clang -fopenmp omp_hello.c -o hello
```

## Practice 1 : OpenMP Hello World

```

```

$ cd Example

$ gcc -fopenmp omp_hello.c -o hello

./hello



\> Note 1：You can set the number of threads visible to OpenMP by

`

$ export OMP\_NUM\_THREADS=num\_of\_threads\_you\_want

`

\> Note 2: Note the difference between \

` omp\_get\_num_threads(); // get thread ID

omp\_get\_num_threads(); // get total number of threads

`

Q1: why we need \`\`\`nthreads, tid\`\`\` to be \`\`\`private\`\`\`?

Q2: Try \`\`\`OMP\_NUM\_THREADS=1000\`\`\` and let elapsed time be t1; try \`\`\`OMP\_NUM\_THREADS=10000\`\`\` and let elapsed time to be t2 on NSCC (note that machine has 24 threads). Do you observe any difference between 10xt1 and t2?

\## OpenMP uses fork-join model

\* start as a single master thread on one core

\* continues as single thread until parallel construct

1\. Paralle region

\> Rule for fortran

a) no \`GOTO\` allowed

b) STOP statements are okay

> Rule for C/C++

- Case sensitive

- structure



# Hands-on with OpenMP

## Do's and Don'ts

- Must be a *DO* or *for* loop (not *DO WHILE*  or *WHILE* )

- Avoid logical dependencies like ```DO A(i) = A(i-1)*2 ENDO```

- Variable declared inside code block becomes "private" by default 

- ```c
  # omp parallel for
  for (int i=0; i<100; ++i)
  {
    // do your work
    // now i is a private to each work thread
  }
  
  ```

## Section Construct

Allowed thread to execute diff. block of code to be done concurently.

Each section is executed once by a thread in the team.

```c```
#progma omp parallel
```

## Single Construct

- Allow only 1 tthread



# OpenMP Clause

- shared

- private

- default

- if

- firstprivate, lastprivate

  - pass value to some certain threads

- num_threads

- reductions

- copyin

## 





# Acknowledgement

The tutorial is based on [OpenMP Exercise](https://computing.llnl.gov/tutorials/openMP/exercise.html) by [Lawrence Livermore National Laboratory](https://www.llnl.gov/) , and NAG training.
