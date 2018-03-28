# Matrix-Multiplication-OpenMP-MPI
</br></br>

The OpenMP-enabled parallel code exploits coarse grain parallelism, which makes use of the cores available in a multicore machine. Basically, I have parallelized the outermost loop which drives the accesses to the result matrix a in the first dimension. 
Thus, work-sharing among the thrads is such that different threads will calculate different rows of the resultant matrix. 
Note that different threads will write different parts of the result in the output array, so we dont’t get any problems during the parallel execution. 
Note that accesses to input matrices are read-only and do not introduce any problems either. 
In the parallelization strategy, we share all the matrices and everything will work fine; in addtion. 
All the indices of the loops are privatized because every thread needs to do it’s own iterations of the loops.
</br>

MPI is a popular mechanism in high performance computing. 
It works for both cluster and shared memory environment. 
The MPI program is launched with multiple processes as multiple workers, hence the memory consumption also multiply up. 
More work would be required to minimize the total memory consumption. 
