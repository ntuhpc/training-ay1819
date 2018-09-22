# Introduction to MPI

## Env

```bash
module load openmpi
```

## Compilation

```bash
mpicc all_avg.c -o all_avg
```

## Run

```bash
mpirun -np 10 a.out 
```