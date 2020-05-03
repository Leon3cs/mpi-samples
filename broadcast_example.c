#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int
		numtasks,		// Number of tasks
		rank,			// Rank of actual process
		root=0,			// Root process that will act as master
		msg;			// Message buffer

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Set the message to only the master process
	if(rank == 0){
		msg=1;
	}else{
		msg=0;
	}

	printf("[Before broadcast] Rank %d | Buffer: %d\n", rank, msg);
	// Synchronize all processes
	MPI_Barrier(MPI_COMM_WORLD);

	// Broadcast message from root to all processes
	MPI_Bcast(&msg, 1, MPI_INT, root, MPI_COMM_WORLD);

	printf("[After broadcast] Rank %d | Buffer: %d\n", rank, msg);

	MPI_Finalize();
}
