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
  double *B =new double[N*N]{0.};
  FillMat(B,N,1);
  double *Z =new double[N*N]{0.};

  TransMAT(A,Z,N);

//  for (size_t ii = 0; ii < N; ii++){
//  for (size_t jj = 0; jj < N; jj++){
//    std::cout<<Z[N*ii+jj]<<" ";
//  }
//  std::cout<<"\n";
//}
 
  std::cout<<Z[0]<<std::endl;
  delete[] A;
  delete[] B;
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
void TransMAT(double *X,double *XT,int N){
#pragma omp parallel
  {
    int nth = omp_get_num_threads();
    int thid = omp_get_thread_num();
    int NSIZE= std::sqrt(nth);
    int Nb= N/NSIZE;
    double *temp =new double[Nb*Nb]{0.};
    int fila= thid%NSIZE;
    int columna= thid/NSIZE;
    
    for (int ii=0; ii<Nb;++ii){
      for (int jj=0;jj<Nb;++jj){
	temp[ii*Nb+jj]=X[(jj+Nb*fila)*N+(ii+Nb*columna)];
      }
    }
    for(int ii=0;ii<Nb;++ii){
      for(int jj=0;jj<Nb;++jj){
	XT[(ii+Nb*columna)*N+(jj+Nb*fila)]=temp[ii*Nb+jj];
      }
    }
    delete[] temp; 
  }

}

