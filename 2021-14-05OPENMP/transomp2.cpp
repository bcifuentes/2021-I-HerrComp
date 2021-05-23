#include <iostream>
#include <omp.h>
#include <random>
#include <cmath>

void FillMat(double *X,int N,int SEED);
void TransMAT(double *X,double *XT,int N);

int main(int argc, char const **argv){
  int N= std::atoi(argv[1]);
  //BLOCKING
  
  double *A =new double[N*N]{0.};
  FillMat(A,N,1);
  double *Z =new double[N*N]{0.};

  TransMAT(A,Z,N);

  // for (size_t ii = 0; ii < N; ii++){
  // for (size_t jj = 0; jj < N; jj++){
  //  std::cout<<Z[N*ii+jj]<<" ";
  //}
  //std::cout<<"\n";
  //}
 
  std::cout<<Z[0]<<std::endl;
  delete[] A;
  delete[] Z;

  return 0;
}

//llenar la matriz
void FillMat(double *X,int N,int SEED){
  std::mt19937_64 gen(SEED);
  std::normal_distribution<double> dis(-100, 100);
  for (size_t ii = 0; ii < N; ii++){
    for (size_t jj = 0; jj < N; jj++){
      X[N*ii+jj] = dis(gen);
    }
  }
}

//transpuesta
void TransMATB(double *X,double *XT,int Nb,int N){
#pragma omp parallel
  {
    if (Nb<=N){
      int NSIZE = N/Nb;
      int nth = omp_get_num_threads();
      int thid = omp_get_thread_num();

      int Nthreat = Nb/nth;
      
      double *temp =new double[Nb*Nb]{0.};
      
      for (int kk=0; kk<NSIZE;++kk){
	for (int ll=0; ll<NSIZE;++ll){
	  for (int ii=Nthreat*thid; ii<Nthreat*(thid+1);++ii){
	    for (int jj=0;jj<Nb;++jj){
	      temp[ii*Nb+jj]=X[(jj+Nb*kk)*N+(ii+Nb*ll)];
	    }
	  }
	  for(int ii=0;ii<Nb;++ii){
	    for(int jj=0;jj<Nb;++jj){
	      XT[(ii+Nb*ll)*N+(jj+Nb*kk)]=temp[ii*Nb+jj];
	    }
	  }
	}
      }
      delete[] temp; 
    }
  }
}

void TransMAT(double *X,double *XT,int N){
  #pragma omp parallel
  
    for(int ii=0;ii<N;++ii){
      for(int jj=0; jj<N;++jj){
	XT[ii*N+jj]=X[jj*N+ii];
      }
    }
  
}
