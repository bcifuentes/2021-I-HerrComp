#include <omp.h>
#include <iostream>
#include <cmath>
#include <random>

int main(int argc, char *argv[]) {
    const int N = 800;
    int i,j;
    double *a = new double[N*N];

#pragma omp parallel 
    {
      std::mt19937_64 gen(1);
      std::normal_distribution<double> dis(-100, 100);
#pragma omp for collapse(2)
      for(i = 0; i < N; i++) {
	for(j=0;j<N;j++){
	  a[i*N+j] = dis(gen);
	}
      }
    }
    

    
    
    delete [] a;
    return 0;
}
