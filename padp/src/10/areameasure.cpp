// find the value of pi
#include <iostream>
#include <omp.h>
#include <stdlib.h>

double getTime(unsigned int n){
    double t1 = omp_get_wtime();
    unsigned int inside = 0, i = 0;
    double x, y, dist;
    // number input

    #pragma omp parallel for num_threads(8) private(x, y, dist) reduction(+ : inside)
    for (i = 0; i < n; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        dist = x * x + y * y; //dist calc

        if (dist <= 1) {
            inside++;
        }
    }
    unsigned int outside = n - inside;
    double t2 = omp_get_wtime();

    // std::cout << "Counts:" << inside << " / " << n << ' ' << (4.0L * inside) / (n) << '\n';
    return t2 - t1;
}

int main()
{
    srand(0);
    for(int i=10000;i<=10000000;i*=10){
        double timeElapsed = getTime(i);
        std::cout<<timeElapsed<<'\n';
    }
}