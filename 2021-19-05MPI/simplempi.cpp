#include <iostream>
#include "mpi.h"

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv); /* Mandatory */
  int pid;
  int np;

  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  for(int ii=0; ii<np;++ii){
    if(ii== pid){ std::cout<< "Hello from pid: " << pid << " out of np: "<< np << "\n";}
    MPI_Barrier(MPI_COMM_WORLD);
  }
  
  MPI_Finalize(); /* Mandatory */
  return 0;
}
