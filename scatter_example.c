#include <mpi.h>
#include <stdio.h>
#define SIZE 5

int main(int argc, char *argv[]){
	int
	numtasks,								// Number of tasks
		rank,								// Rank of actual process
		root=0,								// Root process that will act as master
		sendbuf[SIZE][SIZE]={				// Send buffer
			{1, 2, 3, 4, 5},
			{6, 7, 8, 9, 10},
			{11, 12, 13, 14, 15},
			{16, 17, 18, 19, 20},
			{21, 22, 23, 24, 25}
		},
		recvbuf[SIZE]={0, 0, 0, 0, 0};		// Receive buffer

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0){
		printf("Message to scatter: \n");
		for(int i=0; i<SIZE; i++){
			for(int j=0; j<SIZE; j++){
				printf("%d\t", sendbuf[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	MPI_Barrier(MPI_COMM_WORLD);

	printf("[before scatter] Rank: %d | buffer: %d %d %d %d %d\n",
			rank, recvbuf[0], recvbuf[1], recvbuf[2], recvbuf[3], recvbuf[4]);

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Scatter(&sendbuf, SIZE, MPI_INT, &recvbuf, SIZE, MPI_INT, root, MPI_COMM_WORLD);

	printf("[after scatter] Rank: %d | Buffer: %d %d %d %d %d\n",
			rank, recvbuf[0], recvbuf[1], recvbuf[2], recvbuf[3], recvbuf[4]);

	MPI_Finalize();
}
