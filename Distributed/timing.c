#include <sys/time.h>
#include <stdio.h>

struct timeval tm1, tm2;

void startT()
{
  gettimeofday(&tm1, NULL);
}

void stopT()
{
  gettimeofday(&tm2, NULL);
  unsigned long long t = ((tm2.tv_sec - tm1.tv_sec)*1000000) 
                            + (tm2.tv_usec - tm1.tv_usec);
  printf("\n%llu microseconds occured\n",t);
}
/* copy this block for timing then call start() and stop()***************/


