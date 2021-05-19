#include <omp.h>
#include <iostream>
#include <cmath>
#include <chrono>

//integral 
double integral(double xf, int N);
double integralpar(double xf, int N,int th);
double f(double x);
//metricas
double elapsed(auto start, auto end );
void speed_up(auto start, auto end, double t0,int th);
void parallel_efficiency(auto start, auto end ,double t0 ,int th);

int main (void){
  int N=1500000;
  auto start = std::chrono::steady_clock::now();
  double intp= integralpar(10.,N,1);
  auto end = std::chrono::steady_clock::now();
  double t0=elapsed(start, end); 
  
  for (int th=1;th<14;++th){
    start = std::chrono::steady_clock::now();
    double intp= integralpar(10.,N,th);
    end = std::chrono::steady_clock::now();
    //speed_up(start, end,t0,th);
    parallel_efficiency(start, end,t0,th);
  }

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
double integralpar(double xf, int N,int th) {
  double estimado=0.;
  double dx=xf/N;

#pragma omp parallel num_threads (th)
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

//metricas
void speed_up(auto start, auto end ,double t0 ,int th){
  double speed =  t0/(std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count());
  std::cout << th <<" "<< speed << "\n";
}

void parallel_efficiency(auto start, auto end ,double t0 ,int th){
  double pe =  t0/(th*std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count());
  std::cout << th <<" "<< pe << "\n";  
}


double elapsed(auto start, auto end ){
  return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
}

