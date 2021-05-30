#include <iostream>
#include "mpi.h"

using fptr = double(double);

double f(double x);
double integral(double a,double b,int nsteps,fptr fun);

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv); 
  int pid;
  int np;

  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  integral(0,1,100,f)
  
  MPI_Finalize(); 
  return 0;
}

double f(double x){
  return x*x;
}
double integral(double a,double b,int nsteps,fptr fun){
  double result=0;
  double dx= (b-a)/nsteps;
  for (int ii=0; ii<nsteps;++ii){
    double x= a+ii*dx;
    result+=fun(x);
  }
  return result*dx;
}
