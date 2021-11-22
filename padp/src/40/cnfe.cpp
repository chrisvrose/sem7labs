#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <vector>
/**
 * Sieve
 */
void SieveOfEratosthenes(int n, bool* prime)
{
    auto sqrtnpone = (int)sqrt(n);
    #pragma omp parallel for schedule(guided)
    for (int p = 2; p <= sqrtnpone; ++p) {
        // If prime[p] is not changed,
        // then it is a prime
        if (prime[p]) {
            // Update all multiples
            // of p greater than or
            // equal to the square of it
            // numbers which are multiple
            // of p and are less than p^2
            // are already been marked.
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
}

int main(int, char**)
{
    int n;

    // get n from env
    char* ptr=getenv("ARR_SIZE");
    if(ptr){
        n=atoi(ptr);
        if(n<1){std::cout << "Set ARR_SIZE invalid, defaults to 100000\n"; n=1000;}
    }else{
        n=100000;
       std::cout << "Set ARR_SIZE, defaults to 100000\n"; 
    }

    // Create a boolean array
    // "prime[0..n]" and initialize
    // all entries it as true.
    // A value in prime[i] will
    // finally be false if i is
    // Not a prime, else true.
    bool* prime = new bool[n+1];
    std::fill(prime, prime + n, true);

    auto t1 = omp_get_wtime();

    SieveOfEratosthenes(n, prime);

    auto t2 = omp_get_wtime();

    ulong pcount = 0;
    // Print all prime numbers
    #pragma omp parallel for reduction(+:pcount) schedule(dynamic)
    for (int p = 2; p <= n; p++)
        if (prime[p]) {
            pcount ++;
        }

    auto tinterval = t2 - t1;

    std::cout << "\nRuntime:" << tinterval << " Count:" << pcount << std::endl;

    return 0;
}