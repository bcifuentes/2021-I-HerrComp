#include <iostream>
#include <cstdlib>
#include <cmath>

int foo(int a, int b);
int bar(int a, int b);
double baz(double x);

int main (int argc, char **argv)
{
  int ii, jj;
  ii =  0;
  jj = -1;
  foo(ii, jj);
  foo(jj, ii);//divide por 0
  int kk=2;
  foo(kk,ii);
  
  baz(25.9);

  return EXIT_SUCCESS;
}

int foo(int a, int b)
{
  int result =0;
  if (b !=0){
    result += a/b;
  }
  if (a!=0){
    result += b/a;
  }
  if (bar(a,b)!=0){
    result += b/bar(a,b);
  }
  return result;
}

int bar(int a, int b)
{
  unsigned int c = a;
  return c + a - b;
}

double baz(double x)
{
  if (x == 0) return 0; //no retorna nada, no usa ==, logicamente se cambia por < ya que son double
  //double v = 1-(x+1);//no usa v
  return std::sqrt(x);//punto y coma faltante
}
