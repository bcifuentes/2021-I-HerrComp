#include <iostream>
typedef double REAL;
int main(void){
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);
  REAL under =1.;
  REAL over = 1.;

  for(int ii=1; ii<=1100; ++ii){
    under=under/2;
    over=over*2;
    std::cout << ii<< "\t"<<over<<"\t" << under <<"\n";
  }
  

  return 0;
}
