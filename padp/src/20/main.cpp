// matrix multiplication
/*
 * This C++ program can multiply any two square or rectangular matrices.
 * The below program multiplies two square matrices of size 4 * 4.
 * There is also an example of a rectangular matrix for the same code (commented
 * below). We can change the Matrix value with the number of rows and columns
 * (from MACROs) for Matrix-1 and Matrix-2 for different dimensions.
 */

/*
 * Note:  i- The number of columns in Matrix-1 must be equal to the number of
 * rows in Matrix-2. ii- Output of multiplication of Matrix-1 and Matrix-2,
 * results with equal to the number of rows of Matrix-1 and the number of
 * columns of Matrix-2 i.e. rslt[R1][C2].
 */

#include <iostream>
#include <omp.h>
#include<random>
using namespace std;

int main()
{
    
    int r1, c1, r2, c2;
    cout << "Enter rows and columns for first matrix: ";
    cin >> r1 >> c1;
    cout << "Enter rows and columns for second matrix: ";
    cin >> r2 >> c2;
    int *a = (int*)malloc(r1 * c1*sizeof(int)), *b = (int*)malloc(r2 * c2*sizeof(int)), *mult = (int*)malloc(r1 * c2*sizeof(int));
    if(a==nullptr or b==nullptr or mult==nullptr){return 1;}
    // If column of first matrix in not equal to row of second matrix,
    // ask the user to enter the size of matrix again.
    while (c1 != r2) {
        cout << "Error! column of first matrix not equal to row of second.";

        cout << "Enter rows and columns for first matrix: ";
        cin >> r1 >> c1;

        cout << "Enter rows and columns for second matrix: ";
        cin >> r2 >> c2;
    }

    // Storing elements of first matrix.
    // cout << endl
    //      << "Enter elements of matrix 1:" << endl;
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c1; ++j) {
            // cout << "Enter element a" << i + 1 << j + 1 << " : ";
            // cin >> a[i*r1+j];
            a[i*r1+j] = ((int)random())&((1<<sizeof(int))-1);
        }

    // Storing elements of second matrix.
    // cout << endl
    //      << "Enter elements of matrix 2:" << endl;
    for (int i = 0; i < r2; ++i)
        for (int j = 0; j < c2; ++j) {
            // cout << "Enter element b" << i + 1 << j + 1 << " : ";
            // cin >> b[i*r2+j];
            b[i*r2+j] = ((int)random())&((1<<sizeof(int))-1);
        }
    double x1 = omp_get_wtime();
// Multiplying matrix a and b and storing in array mult.
    int i,j,k;
    #pragma omp parallel for num_threads(8) private(i,j,k)
    for ( i = 0; i < r1; ++i) {
        
        for ( j = 0; j < c2; ++j)
            for ( k = 0; k < c1; ++k) {
                mult[r1*i+j] += a[r1*i+k] * b[r2*k+j];
            }
    }
    double x2 = omp_get_wtime();

    // Displaying the multiplication of two matrix.
    // cout << endl
    //      << "Output Matrix: " << endl;
    // for (int i = 0; i < r1; ++i)
    //     for (int j = 0; j < c2; ++j) {
    //         cout << " " << mult[r1*i+j];
    //         if (j == c2 - 1)
    //             cout << endl;
    //     }
    cout<<"Total time:"<<x2-x1<<'\n';
    return 0;
}