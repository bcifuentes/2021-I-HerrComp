#include <iostream> 
#include <random>
#include <cstdlib>
#include "mpi.h"
double PI(int N,int pid,int np);
void pintar(int N,int pid,int np);
int main(int argc, char ** argv ){
  MPI_Init(&argc, &argv);
  int N= std::atoi(argv[1]);

  int pid;
  int np;
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  pintar(N,pid,np);

  MPI_Finalize(); 
  return 0;
}
void pintar(int N,int pid,int np){
  double pi;
  
  double t0 = MPI_Wtime();
  pi=PI(N,pid,np);
  double t1 = MPI_Wtime();

  if(pid==0){
    std::cout << "pi= "<< pi<<"\n";
    std::cout << "Tiempo con "<<np<<" procesos: " << t1-t0 << "\n";
  }

}
double PI(int N,int pid,int np){
  
  int count = 0;
  int seed = pid; 

  int Nlocal= N/np;
  int iimin= pid*Nlocal;
  int iimax= (pid+1)*Nlocal;

  int tag=0;
  
  std::mt19937 gen(seed);
  std::uniform_real_distribution<double> dis(-1.0, 1.0);
  for (int ii = iimin; ii < iimax; ++ii) {
    double rx = dis(gen);
    double ry = dis(gen);
    if (rx*rx + ry*ry < 1)
      count++;
  }
  if(pid !=0){
    int dest=0;
    MPI_Send(& count,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
  }
  else{
    int aux=0;
    for(int ipid=1;ipid<np;++ipid){
      MPI_Recv(& aux, 1,MPI_INT,ipid,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      count+=aux;
    }
    double pi=4.*count/N;
    return pi;
  }
  return 0;
}
