// testing
#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    cout << "1";
    int x = 0;
    int k;
    cout << "Numdevices" << omp_get_num_threads() << '\n';
    #pragma omp parallel num_threads(4) private(k)
    {
        k = omp_get_thread_num();
        if (k)
        {
            cout << "Odd thread" << k << '\n';
        }
        else
        {
            cout << "Master" << k << '\n';
        }
        #pragma omp atomic
        x += 1;
    }
    cout << "Sum " << x << '\n';



    
}