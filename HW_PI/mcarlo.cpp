#include <iostream> 
#include <random>
#include <cstdlib>
int samples(int N);

int main(int argc, char ** argv ){
  int N= std::atoi(argv[1]);
  int Nc = samples(N);

  double pi = 4.*Nc/N;

  std::cout<<pi<<"\n";
  
  return 0;
}

int samples(int N){
  
    int count = 0;
    int seed = 1; // use pid for seed when in parallel
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dis(-1.0, 1.0);
    for (int ii = 0; ii < N; ++ii) {
    double rx = dis(gen);
    double ry = dis(gen);
    if (rx*rx + ry*ry < 1)
      count++;
  }
  return count;
}
