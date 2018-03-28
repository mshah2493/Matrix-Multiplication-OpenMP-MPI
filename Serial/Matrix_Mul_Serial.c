#include "Header.h"

double *Matrix_Mul_Result = NULL;

int main(int arc, char *argv[])
{
	int i,j,k;
	double result = 0;
	FILE* fp;
	char delim[2];
	
	start();
	
    GetNumbers("inputMatrix1200.csv");
	
	// allocate the memory to the resultant matrix
    Matrix_Mul_Result = (double *)malloc(Matrix_Size * Matrix_Size * sizeof(double));
    		
	for(i = 0; i < Matrix_Size; i++)
	{   	
	   for(j = 0; j < Matrix_Size; j++)
	   {  
		    result = 0;
		    for(k = 0; k < Matrix_Size; k++)
			{	
				result = result + Matrix[i * Matrix_Size + k] * Matrix[k * Matrix_Size + j]; 
			}	
		    Matrix_Mul_Result[i * Matrix_Size + j] = result;
	   }
	}  
	
	
  
  //write the output matrix
  fp = fopen("outputMatrix.csv", "w");
  fprintf(fp, "%d\n", Matrix_Size);
  
  for(j = 0 ; j < Matrix_Size; j++)
  {
    sprintf(delim, "%s", "");
	
    for(i = 0; i < Matrix_Size; i++)
    {
      fprintf(fp, "%s%.2f", delim, Matrix_Mul_Result[j * Matrix_Size + i]);
      sprintf(delim, "%s", ",");;
    }
      fprintf(fp, "\n");
  }
  
  fclose(fp);
  stop();
  
  return 0;
}