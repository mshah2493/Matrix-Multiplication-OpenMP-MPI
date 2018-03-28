#include "Header.h"
double *Matrix = NULL;
int Matrix_Size = 0;
double **ptr;

void GetNumbers(char fileName[])
{

  int j;
  int i;
  char *token;
  size_t len = 0;
  ssize_t read;
  char *line = NULL;
  int lineCount = 0;
  char lineStr[1000000];
  int numbersCount = 0;
  const char delim[2] = ",";
  FILE* fp = fopen(fileName, "rb");

  // Check for file pointer
  if(fp == NULL)
  {
    printf("\nError reading file");
    exit(-1);
  }
  
  while ((read = getline(&line, &len, fp)) != -1) 
  {
    sprintf(lineStr, "%s", line);
	
    if(lineCount == 0)
    {
		// allocate the memory
		Matrix_Size = atoi(line);
		 
		Matrix = (double *)malloc(Matrix_Size * Matrix_Size * sizeof(double));
		if (NULL == Matrix)
		{
			printf("mallloc failed");
			break;
		  }
	}
    else if(lineCount > Matrix_Size)
    {
      break;
    }
    else
    {
	  token =  strtok(lineStr, delim);
  
      while(token != NULL) 
      {
        sscanf(token, "%lf", &Matrix[numbersCount]);
        numbersCount++;
        token = strtok(NULL, delim);
      }
      
	 }
	 
	// free the memory allocated by getline
	if (line != NULL)
	{
	  free(line);
	  line = NULL;
	}
	
    lineCount++;
  }

	 /* allocate the row pointers into the memory */
	 ptr = (double **) malloc (Matrix_Size * sizeof(double*));
	 
	 /* set up the pointers into the contiguous memory */
	for (i = 0; i < Matrix_Size; i++)
	{	
	   (ptr)[i] = &(Matrix[i*Matrix_Size]);
	}
	
  //close fle pointer
  fclose(fp);

}