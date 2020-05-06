#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * MPI Program for calculating pi by numeric integration of
 * the function f(x) = 4 / (1 + x²)
 *
 * The detailed explanation on how the algorithm works is in the comments.
 *
 * For reference on the method for estimate pi see:
 * GROPP, W.; LUSK, E.; SKJELLUM, A. Using MPI: Portable Parallel Programming
 * with the Message-Passing Interface, 3rd Editon, 2014
 * */

int main(int argc, char *argv[])
{
  int
  	  n,										// Number of intervals, the segments of area of the integrand
	  myid,										// The id, or rank, of the process
	  numprocs,									// The total of processes available
	  i,										// Used for iterations on for loop
  	  len;										// Length of the processos name
  double
  	  PI25DT = 3.141592653589793238462643;		// Reference value of pi
  double
  	  mypi,										// Sum of all area segments calculated in that process to calculate pi
	  pi,										// The sum of all pi calculations made by all the slave processes
	  h,										// Constant to limit the range of the area segment
	  sum,										// Accumulates the result of the function at point x
	  x;										// The value of the function at some arbitrary point
  char
  	  hostname[MPI_MAX_PROCESSOR_NAME];			// Hostname of the process
  MPI_Init(&argc,&argv);						// Required function to every MPI program
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);		// Get the number of processes, or tasks, in the communications group
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);			// Get the id, or rank, of the actual process
  MPI_Get_processor_name(&hostname, &len);

  while (1) {
	 /**
	  * Get the number of sections in which the graph will be split
	  * each section will be used to calculate a portion of the
	  * graph's area, the sum of all these areas will result in the
	  * average total area of the graph
	  * */
     if (myid == 0) {
         printf("Enter the number of intervals: (0 quits) ");
         scanf("%d",&n);
     }

     /**
      * Send a message to all slave processes via broadcast with the number of intervals
      * given by the user's input
      * */
     MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

     if (n == 0)
         break;		// Do nothing if the number of intervals is zero
     else {
    	 /**
    	  * h will be used to control the length of the area segments,
    	  * for example, if we want to integrate the function splitting
    	  * it's area in 10 segments, each area segment will be 1/10th the
    	  * length of the interval of integration, in this case, from 0 to 1.
    	  * */
         h   = 1.0 / (double) n;
         /**
          * Initialize the accumulator for the sum with 0
          * */
         sum = 0.0;
         /**
          * Each process with calculate the area of (n * h) area segments of
          * the total function area, in the interval from 0 to 1
          * */
         for (i = myid + 1; i <= n; i += numprocs) {
             x = h * ((double)i - 0.5);														// Get the value of x, based on the length constant
             sum += (4.0 / (1.0 + x*x));													// Compute and sum the value of f(x)
             printf("%s is calculating a fraction of pi\n", hostname);
         }
         mypi = h * sum;																	// Estimate a fraction of pi based on the sum of all computed area segment by this process


         /**
          * Get the estimated fractions of pi from all processes and send to the master process
          * */
         MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
                    MPI_COMM_WORLD);
         if (myid == 0)
             printf("pi is approximately %.16f, Error is %.16f\n",
                    pi, fabs(pi - PI25DT));
     }
  }
  MPI_Finalize();
  return 0;
}

