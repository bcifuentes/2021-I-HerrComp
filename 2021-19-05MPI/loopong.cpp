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
  int p=0;
  for(int ii=0; ii<NPINGPONG;++ii){
    if (pid==p){
      if(ii!=0){
	MPI_Recv(& counter, 1,MPI_INT,(p==0)?1:0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      }
      counter++;
      MPI_Send(& counter,1,MPI_INT,(p==0)?1:0,0,MPI_COMM_WORLD);
    }
    (p==0)?p=1:p=0;
  }

  
  if (pid==(p==0)?1:0){
    std::cout<<counter<<std::endl;
  }
  
  MPI_Finalize();
  return 0;
}
