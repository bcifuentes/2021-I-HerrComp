#include <iostream>
#include <omp.h>
#include <random>
#include <cmath>
#include <chrono>

void FillMat(double *X,int N,int SEED);
void TransMAT(double *X,double *XT,int Nb,int N,int th);
void print_elapsed(auto start, auto end );

int main(int argc, char const **argv){
  int N= std::atoi(argv[1]);
  //BLOCKING
  
  double *A =new double[N*N]{0.};
  FillMat(A,N,1);
  double *Z =new double[N*N]{0.};

  for(int th=1;th<10;++th){
    auto start = std::chrono::steady_clock::now();
    TransMAT(A,Z,64,N,th);
    auto end = std::chrono::steady_clock::now();
    std::cout<<"with "<<th<<" threads\n";
    print_elapsed(start, end);
  }
//  for (size_t ii = 0; ii < N; ii++){
//  for (size_t jj = 0; jj < N; jj++){
//    std::cout<<Z[N*ii+jj]<<" ";
//  }
//  std::cout<<"\n";
//}
 
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
void TransMAT(double *X,double *XT,int Nb,int N,int th){
  int blocksize=Nb;
  int MSIZE=N;
  int i,j,row,col;
#pragma omp parallel for private(i, j, row, col) num_threads (th) schedule(static, 2)
  for ( i = 0; i < MSIZE; i += blocksize) {
    for ( j = 0; j < MSIZE; j += blocksize) {
      for (row = i; row < i + blocksize && row < MSIZE; row++) {
	for (col = j; col < j + blocksize && col < MSIZE; col++) {
	  XT[MSIZE*row+col] = X[MSIZE*col+row];
	}
      }
    }
  }
}

void print_elapsed(auto start, auto end )
{
  std::cout << "Elapsed time in micro-s: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count()
        << "\n";
}
