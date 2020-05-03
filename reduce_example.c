#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

int main(int argc, char *argv[]){
	int
		numtasks,				// Number of tasks
		rank,					// Rank of actual process
		root=0,					// Root process that will act as master
		sendbuf,				// Message buffer for sending messages
		recvbuf_min,			// Message buffer for receiving messages
		recvbuf_max,			// Message buffer for receiving messages
		recvbuf_sum,			// Message buffer for receiving messages
		recvbuf_prod;			// Message buffer for receiving messages

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Generate random number for each process
	srand(time(NULL)+rank);

	sendbuf = rand() % 100;

	printf("[Before reduce] rank: %d | sendbuf: %d\n", rank, sendbuf);

	// Synchronize all processes
	MPI_Barrier(MPI_COMM_WORLD);

	// Call different reduction functions
	MPI_Reduce(&sendbuf, &recvbuf_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(&sendbuf, &recvbuf_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(&sendbuf, &recvbuf_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&sendbuf, &recvbuf_prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

	if(rank == 0){
		printf("[After reduce (Operation MPI_MIN)]: %d\n", recvbuf_min);
		printf("[After reduce (Operation MPI_MAX)]: %d\n", recvbuf_max);
		printf("[After reduce (Operation MPI_SUM)]: %d\n", recvbuf_sum);
		printf("[After reduce (Operation MPI_PROD)]: %d\n", recvbuf_prod);
	}

	MPI_Finalize();
}
