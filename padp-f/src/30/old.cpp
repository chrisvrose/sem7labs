// Bhanu Prakash
// 1RV18CS039
#include <iostream>
#include <math.h>
#include <omp.h>
#include <vector>
using namespace std;
double t = 0.0;

inline long Strike(vector<bool>& composite, long i, long stride, long limit) {
    for (; i <= limit; i += stride)
        composite[i] = true;
    return i;
}

long CacheUnfriendlySieve(long n) {
    long count = 0;
    long m = (long)sqrt((double)n);
    // bool* composite = new bool[n + 1];
    vector<bool> composite(n + 1, false);

    t = omp_get_wtime();

    for (long i = 2; i <= m; ++i)
        if (!composite[i]) {
            ++count;
            // Strike walks array ofsize n here.
            Strike(composite, 2 * i, i, n);
        }

    for (long i = m + 1; i <= n; ++i)
        if (!composite[i]) {
            ++count;
        }
    t = omp_get_wtime() - t;

    // delete[] composite;

    return count;
}

long CacheFriendlySieve(long n) {
    long count = 0;
    long m = (long)sqrt((double)n);
    // bool* composite = new bool[n + 1];
    vector<bool> composite(n + 1, false);

    vector<long> striker;
    vector<long> factor;

    long n_factor = 0;

    t = omp_get_wtime();
    //serial part
    for (long i = 2; i <= m; ++i)
        if (!composite[i]) {
            ++count;
            striker.push_back(Strike(composite, 2 * i, i, m));
            factor.push_back(i);
        }
    n_factor=factor.size();
    // Chops sieve into windows of size ≈ sqrt(n)
    for (long window = m + 1; window <= n; window += m) {
        long limit = min(window + m - 1, n);
        for (long k = 0; k < n_factor; ++k)
            // Strike walks window of size sqrt(n) here.
            striker[k] = Strike(composite, striker[k], factor[k], limit);
        for (long i = window; i <= limit; ++i)
            if (!composite[i])
                ++count;
    }

    t = omp_get_wtime() - t;
    // delete[] striker;
    // delete[] factor;
    // delete[] composite;
    return count;
}

long ParallelSieve(long n) {
    long count = 0;
    long m = (long)sqrt((double)n);
    // long n_factor = 0;
    vector<long> factor;
    t = omp_get_wtime();
    // serial portion -> compute till sqrt(n), setting up the factors
    {
        vector<bool> composite(m + 1, false);

        for (long i = 2; i <= m; ++i)
            if (!composite[i]) {
                ++count;
                Strike(composite, 2 * i, i, m);
                factor.push_back(i);
            }
    }
#pragma omp parallel
    {
        vector<bool> composite(m + 1, false);
        vector<long> striker(m, 0);
        // this is the base to start from, and also if -1, means that strikers must be populated (something this impl doesnt do immediately)
        long base = -1;
#pragma omp for reduction(+ : count)
        for (long window = m + 1; window <= n; window += m) {
            composite.assign(m + 1, false);
            long n_factor = factor.size();
            if (base != window) {
                // Must compute striker from scratch.
                cout<<"Recomputing";
                base = window;
                for (long k = 0; k < n_factor; ++k)
                    striker[k] =
                        (base + factor[k] - 1) / factor[k] * factor[k] - base;
            }
            long limit = min(window + m - 1, n) - base;
            for (long k = 0; k < n_factor; ++k)
                striker[k] =
                    Strike(composite, striker[k], factor[k], limit) - m;
            for (long i = 0; i <= limit; ++i)
                if (!composite[i])
                    ++count;
            base += m;
        }
    }
    t = omp_get_wtime() - t;
    // delete[] factor;
    return count;
}

int main() {
    for (long i = 100000000; i >= 1000000; i /= 10) {
        cout << "Input Size\t" << i << endl;
        long count1 = CacheUnfriendlySieve(i);
        cout << "Unfriendly\t" << count1 << "\t";
        cout << "Time:\t" << t << endl;

        long count2 = CacheFriendlySieve(i);
        cout << "Friendly\t" << count2 << "\t";
        cout << "Time:\t" << t << endl;

        long count3 = ParallelSieve(i);
        cout << "Parallel\t" << count3 << "\t";
        cout << "Time:\t" << t << endl;
    }
}