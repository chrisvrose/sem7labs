// find the value of pi
#include <iostream>
#include <omp.h>
#include <stdlib.h>

int main() {
    unsigned int inside = 0, i = 0,n=10000000;
    double x,y,dist;
    srand(0);
                      // number input

    #pragma omp parallel for num_threads(1) private(x,y,dist) reduction(+:inside)
    for (i = 0; i < n; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        dist = x * x + y * y;           //dist calc

        if (dist <= 1) {
            inside++;
        }
    }
    unsigned int outside = n-inside;
    std::cout << "Counts:" << inside << " / " << n << ' ' << (4.0L * inside) / (n) << '\n';
}