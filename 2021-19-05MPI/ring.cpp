#include <iostream>
#include "mpi.h"


int main(int argn, char ** argv){
  MPI_Init(&argn,&argv);
  const int NPINGPONG =std::atoi(argv[1]);
  int pid;
  int np;
  
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  int counter=0;

  int src=(pid-1+np)%np;
  int dest=(pid+1)%np;
  
  if(pid!=0){
    MPI_Recv(& counter, 1,MPI_INT,src,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  }
  counter+=pid;
  MPI_Send(& counter,1,MPI_INT,dest,0,MPI_COMM_WORLD);
  
  if (pid==0){
    MPI_Recv(& counter, 1,MPI_INT,src,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    std::cout<<counter<<std::endl;
  }
  
  MPI_Finalize();
  return 0;
}
