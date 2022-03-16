#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define BS 32

char m[3][20] = { "Hello\n", "RVCE\n", "CSE\n" };
// mpu
int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    MPI_Status status;
    int rank, size;
    char msg[BS];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (!rank) {
        for (int i = 1; i < size; i++) {
            MPI_Recv(msg, BS, MPI_CHAR,i , 0,MPI_COMM_WORLD,&status);
            printf("Received %.32s is the msg from rank %d/%d\n",msg,rank,size);
        }
    }else{
        MPI_Send(m[((rank-1)%3)],BS,MPI_CHAR,0,0,MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}