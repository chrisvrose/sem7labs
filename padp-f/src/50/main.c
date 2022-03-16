#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

#define BS 20

char m[3][BS] = {"Hello\n", "RVCE\n", "CSE\n"};
// mpu
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    MPI_Status status;
    int rank, size;
    char msg[BS];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank != 0) {
        // for (int i = 1; i < size; i++) {
        MPI_Send(m[((rank - 1) % 3)], BS, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        // }
    } else {
        for (int i = 1; i < size; i++) {
            MPI_Recv(msg, BS, MPI_CHAR, i, 0, MPI_COMM_WORLD,&status);
            printf("Received %.20s is the msg from rank %d/%d\n", msg, i,
                   size);
        }
    }

    MPI_Finalize();
    return 0;
}