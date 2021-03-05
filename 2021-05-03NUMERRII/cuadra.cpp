#include <iostream>
#include <cmath>
typedef double REAL;
REAL suma1(REAL a,REAL b, REAL c);
REAL suma2(REAL a,REAL b, REAL c);
int main(int argn, char ** argv){
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  REAL a=1./4;
  REAL b=1.;
  REAL c=1.;
  int n=std::atoi(argv[1]);
  for (int ii=1;ii<=n;++ii){
    std:: cout << ii <<"\t"<< suma1(a,b,c) <<"\t" << suma2(a,b,c)<<"\n";
    c=c/10;

  }
  return 0;
}
REAL suma1(REAL a, REAL b, REAL c){
  REAL xn=(-b+std::sqrt(b*b-4*a*c))/(2*a);
  return xn;
}
REAL suma2(REAL a,REAL b, REAL c){
  REAL xn=-2*c/(b+std::sqrt(b*b-4*a*c));
  return xn;
}
//verificado
