#include "Header.h"

double *Matrix1 = NULL;
double *Matrix_Mul_Result = NULL;
double *Matrix_Mul_Result1 = NULL;

int main (int argc, char *argv[])
{
	//int numtasks, Send_tag = 0, Recv_tag = 1, rank, rc, start, reminder, num_rows, i, j, k;
	int numtasks, rank, i, j, k, rc, num_rows;
	double result = 0;
	FILE* fp;
	char delim[2];
	
	MPI_Status stat;
		
	/* Initialize the MPI environment */
	rc = MPI_Init(&argc, &argv);
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
		startT();
		GetNumbers("inputMatrix1200.csv");
		
		/* allocate the memory to the resultant matrix */
		Matrix_Mul_Result = (double *)malloc(Matrix_Size * Matrix_Size * sizeof(double));

		num_rows = Matrix_Size / numtasks;
	} 
	
	MPI_Bcast (&Matrix_Size, 1 , MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast (&num_rows, 1 , MPI_INT, 0, MPI_COMM_WORLD);
	
	if (rank > 0)
	{
		Matrix = (double *)malloc(Matrix_Size * Matrix_Size * sizeof(double));
	}

	/* broadcast a copy of Matrix to all the slave nodes */ 
	MPI_Bcast (Matrix, Matrix_Size * Matrix_Size , MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	/* Creating matrix to receive porting of Matrix at each node in the communicator */
	Matrix1 = (double *)malloc(num_rows * Matrix_Size * sizeof(double));
	
	MPI_Scatter(Matrix, num_rows*Matrix_Size, MPI_DOUBLE, Matrix1, num_rows*Matrix_Size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
		
	/* allocate the memory to the portion of resultant matrix on each node */
	Matrix_Mul_Result1 = (double *) malloc (num_rows * Matrix_Size * sizeof(double));
	
	omp_set_num_threads(2);	
	
	#pragma omp parallel private(i,j,k) 
	{
	#pragma omp for schedule(dynamic,chunk) reduction(+:result)
	for(i = 0; i < num_rows; i++)
	{   	
	   for(j = 0; j < Matrix_Size; j++)
	   {  
		    result = 0;
		    for(k = 0; k < Matrix_Size; k++)
			{	
				result = result + Matrix1[i * Matrix_Size + k] * Matrix[k * Matrix_Size + j]; 
			}	
		    Matrix_Mul_Result1 [i * Matrix_Size + j] = result;
	   }
	}
			
	}
	
	MPI_Gather(Matrix_Mul_Result1, num_rows*Matrix_Size, MPI_DOUBLE, Matrix_Mul_Result, num_rows*Matrix_Size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		
	if(rank == 0)
	{		
		//write the output matrix
		fp = fopen("outputMatrix.csv", "w");
		fprintf(fp, "%d\n", Matrix_Size);
  
		for(j = 0 ; j < Matrix_Size; j++)
		{
			sprintf(delim, "%s", "");
	
			for(i = 0; i < Matrix_Size; i++)
			{
				fprintf(fp, "%s%.2f", delim, Matrix_Mul_Result[j * Matrix_Size + i]);
				sprintf(delim, "%s", ",");
			}
			
			fprintf(fp, "\n");
		}
  
		fclose(fp);
		stopT();
	}		
	MPI_Finalize();
	return 0;
}
