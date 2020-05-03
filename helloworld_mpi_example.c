#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int numtasks,
		rank,
		len,
		rc;
	char hostname[MPI_MAX_PROCESSOR_NAME];

	// initialize MPI
	MPI_Init(&argc, &argv);

	// get number of task
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	// get my rank
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// get my processor name
	MPI_Get_processor_name(hostname, &len);

	// prints on screen all environment management routines data
	printf("Number of tasks= %d | My rank: %d | Running on: %s\n", numtasks, rank, hostname);

	MPI_Finalize();
}
