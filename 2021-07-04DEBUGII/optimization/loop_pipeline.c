#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  const int n = 512;
  float ***a;
  clock_t cputime1, cputime2;
  int i,j,k,ones;

  // Allocating memory for array/matrix
  a = malloc(n*sizeof(float **));
  for (i=0; i<n; i++){
    a[i] = malloc(n*sizeof(float*));
    for (j=0; j<n; j++)
      a[i][j] = malloc(n*sizeof(float));
  }

  cputime1 = clock();
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      for (k=0; k<n; k++){
        if (ones == 1)
          a[i][j][k] = 1;
        else
          a[i][j][k] = 0;
      }
  cputime2 = clock() - cputime1;
  printf("Time with conditional inside: %f\n", ((double)cputime2)/CLOCKS_PER_SEC);

  cputime1 = clock();
  if (ones == 1){
    for (i=0; i<n; i++)
      for (j=0; j<n; j++)
        for (k=0; k<n; k++)
          a[i][j][k] = 1;
  }
  else{
    for (i=0; i<n; i++)
      for (j=0; j<n; j++)
        for (k=0; k<n; k++)
          a[i][j][k] = 0;
  }
  cputime2 = clock() - cputime1;
  printf("Time with conditional outside: %f\n", ((double)cputime2)/CLOCKS_PER_SEC);


  return 0;

}
