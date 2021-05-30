#include <iostream>
#include "mpi.h"

const int NS= 10;

void fill(double *data, int NS, int NSlocal, int pid, int np);
void print_local(double *data, int NS, int NSlocal, int pid, int np);
void print(double *data, int NS, int NSlocal, int pid, int np);
void average(double *data, int NS, int NSlocal, int pid, int np);
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

  average(data,NS,NSlocal,pid,np);
  
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
void print_local(double *data, int NS, int NSlocal, int pid, int np){
  std::cout<< "pid:" << pid << "\n";
  for(int ilocal=0;ilocal<NSlocal;++ilocal){
    std::cout<<data[ilocal]<<" ";
  }
  std::cout<< "\n";

}
void print(double *data, int NS, int NSlocal, int pid, int np){
  int tag=0;
  if (pid==0){
    double * aux = new double [NSlocal] {0.};
    print_local(data, NS,NSlocal,pid,np);
    
    for (int ipid=1;ipid<np;++ipid){
      MPI_Recv(aux, NSlocal,MPI_DOUBLE,ipid,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      print_local(aux, NS,NSlocal,ipid,np);
    }
    delete [] aux;
  }
  else {
    int dest=0;
    MPI_Send(data, NSlocal,MPI_DOUBLE,dest,tag,MPI_COMM_WORLD);
  }

}

void average(double *data, int NS, int NSlocal, int pid, int np){
  if (pid==0){
    double average=0;
    double suma=0;
    for(int ilocal=1;ilocal<NSlocal;++ilocal){
      suma+=data[ilocal];
    }
    average+=suma;
    for(int ipid=1;ipid<np;++ipid){
      MPI_Recv(& suma, 1,MPI_DOUBLE,ipid,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);	    
      average+=suma;
    }
    std::cout<<average/NS<<std::endl;
  }
  else {
    double suma=0;
    int dest=0;
    for(int ilocal=0;ilocal<NSlocal;++ilocal){
      suma+=data[ilocal];
    }
    MPI_Send(& suma,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
  }

}



