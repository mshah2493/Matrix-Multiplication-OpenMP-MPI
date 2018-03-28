#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int numtasks, Send_tag = 0, Recv_tag = 1, rank, rc;
	
	MPI_Status status;
	
	/* Initialize the MPI environment */
	rc = MPI_Init(int *argc, char ***argv);
	if (rc != MPI_SUCCESS)
	{
		printf ("Error starting MPI program. Terminating. \n");
		MPI_Abort (MPI_COMM_WORLD, rc);
	}
	
	/* Get the number of processes */
	MPI_Comm_size (MPI_COMM_WORLD, &numtasks);

	/* Get the rank of the process */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
			
	if (rank == 0)
	{	
		int start, reminder, num_elements;
		double result;
		
		double arr[] = {1,2,3,4,5,6,7,8,8,9}
		
		int arr_Size = sizeof(arr) / sizeof(arr[0]);  
		
		reminder = arr_Size % numtasks;
				
		for (i = 0; i < numtasks; i++)
		{	
			start = 0;
			num_elements = 0;
			
			if (i < reminder)
			{
				num_elements = arr_Size / numtasks + 1;
			}
			else 
			{
				num_elements = arr_Size / numtasks;
			}
			
			start = start + i * num_elements;
				
			/* Send devided matrix to all the nodes including Master node */
		
			MPI_Send(&start, 1, MPI_INT, i, Send_tag, MPI_COMM_WORLD);
			MPI_Send(&num_elements, 1, MPI_INT, i, Send_tag, MPI_COMM_WORLD);
			MPI_Send(&arr[start], num_elements, MPI_DOUBLE, i, Send_tag, MPI_COMM_WORLD);		
		}
	} 
	
	
	int startR;
	int num_elementsR;
	double resultR = 0;
	/* Receiving Matrix by all the nodes in the communicator */
	MPI_Recv(&startR, 1, MPI_INT, 0, Send_tag, MPI_COMM_WORLD, &status);
	MPI_Recv(&num_elementsR, 1, MPI_INT, 0, Send_tag, MPI_COMM_WORLD, &status);
 
	double *arrR = (double *) malloc (num_elementsR * sizeof(double));	

	MPI_Recv(arrR, num_elementsR, MPI_DOUBLE, 0, Send_tag, MPI_COMM_WORLD, &status);
		
	for(i = 0; i < num_elementsR; i++)
	{
		resultR = resultR + arrR[i];
	}	
	

	// Sending resultant matrix to master node
	MPI_Send(&startR, 1, MPI_INT, 0, Recv_tag, MPI_COMM_WORLD);
    MPI_Send(&num_elementsR, 1, MPI_INT, 0, Recv_tag, MPI_COMM_WORLD);
    MPI_Send(&resultR, 1, MPI_DOUBLE, 0, Recv_tag, MPI_COMM_WORLD);
	
	if(rank == 0)
	{	
		for(i = 0; i < numtasks; i++)
		{
			MPI_Recv(&start, 1, MPI_INT, 0, Recv_tag_tag, MPI_COMM_WORLD, &status);
			MPI_Recv(&num_elements, 1, MPI_INT, 0, Recv_tag_tag, MPI_COMM_WORLD, &status);
			MPI_Recv(&result, num_elements, MPI_DOUBLE, Recv_tag, MPI_COMM_WORLD, &status);	
		}	
		
		printf("result : %.2lf\n", result);
    }
	
   MPI_Finalize();
	
	return 0;
}
