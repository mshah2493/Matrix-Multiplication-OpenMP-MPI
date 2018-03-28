#include<stdio.h>
#include<stdio.h>
#include "time.h"
#include<stdlib.h>
//prototype
double getRand(double min, double max);

int main(int argc, char*argv[])
{
  if(argc<2)
  {
    perror("\nUsage ./generateInput <squareMatrixSize>\n");
    exit(-1);
  }
  FILE *fp;
  int matrixSize = atoi(argv[1]), i, j;
  double min=0.00001, max=100000;
  char comma[2];
  fp = fopen("inputMatrix.csv", "w");
  srand(time(NULL));
  fprintf(fp, "%d\n", matrixSize);
  for(i=0;i<matrixSize;i++)
  {
    sprintf(comma, "%s", "");
    for(j=0;j<matrixSize;j++)
    {
      fprintf(fp, "%s%f",comma,getRand(min, max));
      sprintf(comma, "%s", ",");;
    }
      fprintf(fp, "\n");
  }
  
  fclose(fp);

}

double getRand(double min, double max)
{
    double d = (double)rand() / RAND_MAX;
    return min + d * (max - min);
}