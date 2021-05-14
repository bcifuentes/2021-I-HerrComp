#include <omp.h>
#include <iostream>
#include <cmath>

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
    int ii;
#pragma omp parallel for 
    for(ii = 0; ii < size; ii++) {
      a[ii] = 50*ii*std::sin(ii) ;
    }    
}

double average(double *a, int size)
{
    double result = 0;
#pragma omp parallel for reduction(+:result) 
    for(int ii = 0; ii < size; ++ii) {
        result += a[ii];
    }
    result /= size;
    return result;
}
