#include <mpi.h>
#include <stdio.h>
#define MSG_SIZE 1

int main(int argc, char *argv[]){
	int
		numtasks, 	// Number of tasks
		rank,		// Rank of the actual process
		count,		// Count of messages received
		tag=1;		// Unique message identification

	char
		inputmsg = "i",		// Input message
		outputmsg = "o";	// Output message
	MPI_Status Stat;	// Status object for receiving messages

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0){
		int dest_rank = 1;
		int source_rank = rank;
		char recvmsg;

		// Send a message to dest_rank
		MPI_Send(&inputmsg, MSG_SIZE, MPI_CHAR, dest_rank, tag, MPI_COMM_WORLD);
		// Receive a message from dest_rank
		MPI_Recv(&recvmsg, MSG_SIZE, MPI_CHAR, dest_rank, tag, MPI_COMM_WORLD, &Stat);
	}

	if(rank == 1){
		int dest_rank = 0;
		int source_rank = rank;
		char recvmsg;

		// Receive a message from dest_rank
		MPI_Recv(&recvmsg, MSG_SIZE, MPI_CHAR, dest_rank, tag, MPI_COMM_WORLD, &Stat);
		// Send a message to dest_rank
		MPI_Send(&outputmsg, MSG_SIZE, MPI_CHAR, dest_rank, tag, MPI_COMM_WORLD);
	}

	// Get the total count o f messages of type char that were sent
	MPI_Get_count(&Stat, MPI_CHAR, &count);
	if(rank == 0 || rank == 1){
		printf("Task %d received %d messages from %d with tag %d\n",
					rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
	}

	MPI_Finalize();
}
