// find the value of pi
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#define IT (1<<25)
int main(){
    float x,y,dist;long count=0;
    srand(0);
    double t = omp_get_wtime();
    #pragma omp parallel for num_threads(6) private(x,y,dist) reduction(+:count)
    for(int i=0;i<IT;i++){
        x = ((float)rand())/RAND_MAX;
        y = ((float)rand())/RAND_MAX;
        dist = x*x+y*y;
        if(dist<1){count++;}
    }
    t = omp_get_wtime()-t;
    std::cout<<"PI is approximately "<<((float)(4*count)/IT)<<",t="<<t<<'\n';
}