#include <mpi.h>
#include <stdio.h>
#define MSG_SIZE 1
#define BUFFER_SIZE 2
#define REQS_LENGTH 4
#define STATS_LENGTH 4

int main(int argc, char *argv[]){
	int
		numtasks,					// Number of tasks
		rank,						// Rank of actual process
		tag1=1,						// Used for message identification
		tag2=2,						// Used for message identification
		next,						// Points to the next neighbor
		prev,						// Points to the previous neighbor
		count=1,						// Messages count
		buf[BUFFER_SIZE];			// Messages Array

	MPI_Request reqs[REQS_LENGTH];			// Requests array for handle message sending
	MPI_Status stats[STATS_LENGTH];			// Status array for handle awaiting

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Calculations for get the previous and next neighbors of actual rank
	prev = rank - 1;
	next = rank + 1;
	if(rank == 0) prev = numtasks - 1;
	if(rank == (numtasks - 1)) next = 0;

	// Receive messages from adjacent neighbors
	MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
	MPI_Irecv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[1]);

	// Send messages to adjacent neighbors
	MPI_Isend(&rank, 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[2]);
	MPI_Isend(&rank, 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[3]);

	printf("Process %d sending message to %d and %d\n", rank, prev, next);

	MPI_Waitall(REQS_LENGTH, reqs, stats);

	MPI_Finalize();
}
