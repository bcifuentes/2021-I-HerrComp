#include <omp.h>
#include <iostream>
#include <cmath>
#include <cstdio>
void fill_data(double *a, int size);
double average(double *a, int size);

int main(int argc, char *argv[]) {
    std::cout.precision(15); std::cout.setf(std::ios::scientific);
    
    const int N = 4000;
    double *a = new double[N];

    fill_data(a, N);
    std::cout << a[1] << std::endl;
    double avg = average(a, N);
    std::cout << avg << "\n";
    
    delete [] a;
    return 0;
}

void fill_data(double *a, int size){
  int i;
#pragma omp parallel private(i)
  {
    int thid = omp_get_thread_num();
    int nth = omp_get_num_threads();
    int localsize = size/nth;
    int iimin = thid*localsize;
    int iimax = iimin + localsize;
    for(i = iimin; i < iimax; i++) {
      a[i] = 50*i*std::sin(i);
    }
  }
}

double average(double *a, int size){
  int thid;
  double result=0.;
#pragma omp parallel private(thid)
  {
    thid = omp_get_thread_num();
    int nth = omp_get_num_threads();
    int Nsize= size/nth;
    
    int suma;
    for(int ii =Nsize*(thid); ii< Nsize*(thid+1);++ii){
      suma += a[ii];
    }
    #pragma omp atomic
    result+=suma;
  }
  result /= size;
  return result;

}
