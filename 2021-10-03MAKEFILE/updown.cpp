#include <iostream>
#include <cmath>
typedef float REAL;

REAL sum1(int n);
REAL sum2(int n);

int main(void){
  std::cout.precision(7);
  std::cout.setf(std::ios::scientific);
  int n=1000;
  for (int ii=1;ii<n;++ii){
    std::cout<< ii<<"\t"<<sum1(ii)<<"\t"<<sum2(ii)<<"\t"<<(std::fabs(sum1(ii)-sum2(ii)))/sum2(ii)<<"\n";
  }

  return 0;
}
REAL sum1(int n){
  REAL suma=0.;
  for (int ii=1 ;ii<=n;++ii){
    suma=suma+1./ii;
  }
  return suma;
}

REAL sum2(int n){
  REAL suma=0.;
  for (int ii=0 ;ii<n;++ii){
    suma=suma+1./(n-ii);
  }
  return suma;
}
