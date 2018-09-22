#include <mpi.h>
#include <stdio.h>

#define NUM_ELE_PER_RANK 10

double *create_matrix(int num_elements) {
    double *matrix = (double *)malloc(sizeof(double) * num_elements);
    int i;
    for (i = 0; i < num_elements; i++) {
        matrix[i] = (double) i;
    }
    return matrix;
}

double compute_avg(double *array, int num_elements) {
    double sum = 0.f;
    int i;
    for (i = 0; i < num_elements; i++) {
        sum += array[i];
    }
    return sum / num_elements;
}


void print_matrix(double* matrix, int row, int col) {
    int i,j;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++)
            printf("%lf ", matrix[i * col + j]);
        printf("\n");
    }
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double* all_values,*all_local_avgs;
    double local_avg;

    if (world_rank == 0) {
        all_values = create_matrix(world_size * NUM_ELE_PER_RANK);
        print_matrix(all_values, world_size, NUM_ELE_PER_RANK);
    }

    double *local_part = malloc(sizeof(double) * NUM_ELE_PER_RANK);

    MPI_Scatter(all_values, NUM_ELE_PER_RANK, MPI_DOUBLE, local_part,
                NUM_ELE_PER_RANK, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    local_avg = compute_avg(local_part, NUM_ELE_PER_RANK);
    printf("Rank %d local avg: %lf\n", world_rank, local_avg);

    if (world_rank == 0) {
        all_local_avgs = malloc(sizeof(double) * world_size);
    }

    MPI_Gather(&local_avg, 1, MPI_DOUBLE, all_local_avgs, 1, MPI_DOUBLE, 0,
               MPI_COMM_WORLD);


    if (world_rank == 0) {
        double avg = compute_avg(all_local_avgs, world_size);
        printf("All avg: %lf\n", avg);
    }

    if (world_rank == 0) {
        free(all_values);
        free(all_local_avgs);
    }
    free(local_part);

    MPI_Finalize();
}
