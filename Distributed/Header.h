#include <mpi.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include<omp.h>
 
#define chunk 10

void GetNumbers(char fileName[]);

extern double *Matrix;
extern int Matrix_Size;