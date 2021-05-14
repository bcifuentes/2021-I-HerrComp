#include <cstdio>

int main(void)
{
    double x = 9.0;
#pragma omp parallel num_threads(4)
    {// se generan los threads
        std::printf("Hello, world.\n");
    } // mueren los threads
    
    return 0;
}
