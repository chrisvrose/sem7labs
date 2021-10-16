// find the value of pi
#include <iostream>
#include <omp.h>
// #include<random>
#include <stdlib.h>
int halfrand = RAND_MAX >> 1;
int main()
{

    int outside = 0, inside = 0,i=0;
    srand(0);
#pragma omp parallel for num_threads(4) private(i)
    for (i = 0; i < 1<<30; i++) {
        unsigned int r1 = rand();
        unsigned int r2 = rand();
        double x = ((double)r1 - halfrand) / (halfrand);
        double y = ((double)r2 - halfrand) / (halfrand);
        double dist = x * x + y * y;
        // std::cout<<r1<<' '<<r2<<' '<<"dist"<<dist<<"\n";
        
        if (dist > 1) {
            #pragma omp atomic
            outside++;
        } else {
            #pragma omp atomic
            inside++;
        }
    }

    std::cout<<"Counts:"<<inside<<' '<<outside+inside<<' '<<(4.0f*inside)/(outside+inside)<<'\n';
}