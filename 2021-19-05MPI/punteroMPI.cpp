#include <iostream>
#include "mpi.h"

const int NS= 10;

void fill(double *data, int NS, int NSlocal, int pid, int np);
void print(double *data, int NS, int NSlocal, int pid, int np);
int main(int argn, char ** argv){
  MPI_Init(&argn,&argv);
  int pid;
  int np;

  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  const int NSlocal=NS/np;
  double * data = new double [NSlocal]{0.};
  
  fill(data, NS,NSlocal,pid,np);
  print(data, NS,NSlocal,pid,np);
  delete [] data;
  MPI_Finalize();

  return 0;
}
void fill(double *data, int NS, int NSlocal, int pid, int np){
  for(int ilocal=0;ilocal<NSlocal;++ilocal){
    int iglobal=NSlocal*pid+ilocal;
    data[ilocal]=2*iglobal;
  }
}
void print(double *data, int NS, int NSlocal, int pid, int np){
  std::cout<< "pid:" << pid << "\n";
  for(int ilocal=0;ilocal<NSlocal;++ilocal){
    std::cout<<data[ilocal]<<" ";
  }
  std::cout<< "\n";

}
