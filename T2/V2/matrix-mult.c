#include <stdio.h>
#include "mpi.h"

void printMatrix(int rows, int columns, int matrix[rows][columns])
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%d     ", matrix[i][j]);
        }
        printf("\n");
    }
}

main(int argc, char **argv)
{
    int my_rank;                                    // process identifier
    int workers_total;                              // total amount of workers

    int processor_buffer_length = MPI_MAX_PROCESSOR_NAME;  
    char masterHostname[processor_buffer_length];    // host where the master process is currently running on

    // MPI initialization
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &workers_total);  

    // master sends its hostname to all workers (this same BCast call is used by both master and slaves)
    MPI_Get_processor_name(masterHostname, &processor_buffer_length); 
    MPI_Bcast(&masterHostname, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        /**************** MASTER ****************/

        printf("\n[MASTER] - executado no host %s\n", masterHostname);
    }
    else
    {
        /**************** WORKER ****************/

        printf("\n[ESCRAVO-%d] - executado no host %s\n", my_rank, masterHostname);
    }

    MPI_Finalize();
}