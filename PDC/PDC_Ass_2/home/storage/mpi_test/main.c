#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Initialize MPI
    
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get the number of processes
    
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get the rank of each process
    
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len); // Get processor name
    
    printf("Hello from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);
    
    MPI_Finalize(); // Finalize MPI
    return 0;
}
