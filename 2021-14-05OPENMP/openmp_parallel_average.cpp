#include <omp.h>
#include <iostream>
#include <cmath>

void fill_data(double *a,int N);

int main(int argc, char *argv[]) {
    const int N = 10000000;
    int i;
    double *a = new double[N];

    fill_data(a,N);
    std::cout << a[1] << "\n";
    
    delete [] a;
    return 0;
}

void fill_data(double *a,int N){
  int i;
#pragma omp parallel for
        for(i = 0; i < N; i++) {
            a[i] = 2*i*std::sin(std::sqrt(i/56.7)) +
                std::cos(std::pow(i*i, 0.3));
        }
}

