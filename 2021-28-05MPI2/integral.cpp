#include <iostream>
#include "mpi.h"

using fptr = double(double);

double f(double x);

double integralp(double a,double b,int nsteps,fptr fun, int pid,int np);
void integral(double a,double b,int nsteps,fptr fun, int pid,int np);
int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv); 
  int pid;
  int np;

  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  double a=0;
  double b=1;
  int N=10000;

  integral(a,b,N,f,pid,np);
  
  
  MPI_Finalize(); 
  return 0;
}

double f(double x){
  return x;
}
void integral(double a,double b,int nsteps,fptr fun, int pid,int np){
  double val =integralp(a,b,nsteps,fun,pid,np);
  if(pid!=0){
    //enviar val a pid 0
    MPI_Send(& val, 1, MPI_DOUBLE,0,0,MPI_COMM_WORLD);
  }
  else{
    for(int ii=1;ii<np;++ii){
      double aux;
      MPI_Recv(& aux, 1 ,MPI_DOUBLE,ii,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      val+=aux;
    }
    std::cout<<val<<"\n";
  }
}
double integralp(double a,double b,int nsteps,fptr fun, int pid,int np){
  double result=0;
  double dx= (b-a)/nsteps;
  int Nlocal= nsteps/np;
  int iimin = pid*Nlocal;
  int iimax=(pid+1)*Nlocal;
  for (int ii=iimin; ii<iimax;++ii){
    double x= a+ii*dx;
    result+=fun(x);
  }
  result *=dx;
  return result;
}
