#include <omp.h>
#include <iostream>
#include <cmath>
double integral(double xf, int N);
double integralpar(double xf, int N);
double f(double x);
int main (void){
  int N=1500000;
  
  std::cout<< integralpar(10.,N)<<std::endl;
  return 0;
}


double f(double x){
  double y=std::sin(x*std::sin(x))*x*x+5*x*std::cos(x*x);
  return y;
}
double integral(double xf, int N){
  double estimado=0.;
  double dx=xf/N;
  for(int ii=0; ii<N;++ii){
    estimado+=f(ii*dx)*dx;
  }
  return estimado;
}
double integralpar(double xf, int N) {
  double estimado=0.;
  double dx=xf/N;

#pragma omp parallel 
  {
    int thid = omp_get_thread_num();
    int nth = omp_get_num_threads();
    int Nsize= N/nth;
    double estimadoth;
    for(int ii =Nsize*(thid); ii< Nsize*(thid+1);++ii){
      estimadoth+=f(ii*dx)*dx;
    }
    #pragma omp atomic
    estimado+=estimadoth;
  }
  return estimado;
} 
