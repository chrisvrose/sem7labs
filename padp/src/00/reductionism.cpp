#include<iostream>
using namespace std;
int main(){
    int sum=10;
        cout<<"sum "<<sum<<"\tAddress " <<&sum <<'\n';
    int i;

    #pragma omp parallel for  reduction(+ : sum) private(i)
    for ( i = 1; i <= 4; i++)
    {
        
        cout<<"sum "<<sum<<"\tAddress " <<&sum <<'\n';

        sum += i;
    }


    cout<<"sum "<<sum<<"\tAddress " <<&sum <<'\n';
    return 0;
}