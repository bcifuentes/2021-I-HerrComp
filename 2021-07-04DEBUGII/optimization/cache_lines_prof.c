/* Program showing cache misses while filling an array comparing
 * row-major versus column-major order. Intended to use with
 * a memory profiler.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global consants
#define n 512

// Function prototyping
void rowfill(float ***);
void columnfill(float ***);

int main(){
  clock_t cputime1, cputime2;
  float ***a;
  int i,j;

  // Allocating memory for array/matrix
  a = malloc(n*sizeof(float **));
  for (i=0; i<n; i++){
    a[i] = malloc(n*sizeof(float*));
    for (j=0; j<n; j++)
      a[i][j] = malloc(n*sizeof(float));
  }
  cputime1 = clock();
  rowfill(a);
  cputime2=clock() - cputime1;
  printf("Time with fast index inside: %lf\n", ((double)cputime2)/CLOCKS_PER_SEC);

  cputime1 = clock();
  columnfill(a);
  cputime2=clock() - cputime1;
  printf("Time with fast index outside: %lf\n", ((double)cputime2)/CLOCKS_PER_SEC);

  // Clearing memory
  for (i=0; i<n; i++){
    for (j=0; j<n; j++)
      free(a[i][j]);
    free(a[i]);
  }
  free(a);

  return 0;
}

void rowfill(float ***a){
  int i,j,k;
  for (k=0; k<n; ++k)
    for (j=0; j<n; ++j)
      for (i=0; i<n; ++i)
        a[i][j][k] = 1.0;
}

void columnfill(float ***a){
  int i,j,k;
  for(i=0; i<n; ++i)
    for (j=0; j<n; ++j)
      for (k=0; k<n; ++k)
        a[i][j][k] = 1.0;
}
