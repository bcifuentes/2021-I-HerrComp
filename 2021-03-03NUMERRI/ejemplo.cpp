#include<iostream>
int main(void){
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
  double a= 0.;
  for(int ii =1 ;ii<=10;ii++){
    a+=0.1;
  }
  std::cout << a  <<"\n";

  return 0;
}
