# Introduction to MPI

In this example, we will use basic MPI operations to calculate the average value of a matrix.

## Algorithm

* Rank 0 firstly initialized the matrix, which is stored in `all_values`.
* Every rank call `MPI_Scatter` to split the matrix into multiple parts with same size `NUM_ELE_PER_RANK`, which is stored in `local_part`.
* Every rank calculate the average of its `local_part` and store in `local_avg`.
* Every rank call `MPI_Gather` to collect every rank's `local_avg` into `all_local_avgs`.
* Rank 0 calculate the average of `all_local_avgs`, and `avg` is the average value of the matrix `all_values`.

```
               all_values                                                                              
           ┌────────────────┐               local_part       local_avg          all_local_avgs     avg 
           │ 0  1  2  3  4  │                                                                          
Rank0      │ 5  6  7  8  9  │MPI_Scatter ┌───────────────┐ avg  ┌──┐MPI_Gather ┌─────────────┐avg ┌───┐
           │ 10 11 12 13 14 │─────┬─────▶│ 0  1  2  3  4 ├─────▶│2 │─────┬────▶│ 2  7  12 17 │───▶│9.5│
           │ 15 16 17 18 19 │     │      └───────────────┘      └──┘     │     └─────────────┘    └───┘
           └────────────────┘     │      ┌───────────────┐ avg  ┌──┐     │                             
Rank1                             ├─────▶│ 5  6  7  8  9 │─────▶│7 │─────┤                             
                                  │      └───────────────┘      └──┘     │                             
                                  │      ┌───────────────┐ avg  ┌──┐     │                             
Rank2                             ├─────▶│10 11 12 13 14 │─────▶│12│─────┤                             
                                  │      └───────────────┘      └──┘     │                             
                                  │      ┌───────────────┐ avg  ┌──┐     │                             
Rank3                             └─────▶│15 16 17 18 19 ├─────▶│17│─────┘                             
                                         └───────────────┘      └──┘                                   
```

## Load Dependency
After login to NSCC,

```bash
module load openmpi
```

## Compilation

```bash
mpicc all_avg.c -o all_avg
```

## Run

```bash
# make sure np does not exceeds total number of cores on the machine
mpirun -np 10 all_avg 
```

## Question
* What happens if `np` is greater than the number of cores?

