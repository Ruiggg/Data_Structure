#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "SparseMatrix.h"

int main()
{
    RLSMatrix M;
    M.data[1].i=0;
    M.data[1].j=0;
    M.data[1].e=3;
    M.data[2].i=0;
    M.data[2].j=3;
    M.data[2].e=5;
    M.data[3].i=1;
    M.data[3].j=1;
    M.data[3].e=-1;
    M.data[4].i=2;
    M.data[4].j=0;
    M.data[4].e=2;

    M.mu = 3;
    M.nu = 4;
    M.tu = 4;
    Rpos(&M);
    PrintRLSMatrix(M);
    RLSMatrix T;
    //FastTransposeSMatrix(M,&T);
    //printf("After transposing it:\n");
    //if(FastTransposeSMatrix(M,&T)==OK)
    //    PrintSMatrix(T);
    // else
    //    printf("ERROR happens!\n");
    T.data[1].i=0;
    T.data[1].j=1;
    T.data[1].e=2;
    T.data[2].i=1;
    T.data[2].j=0;
    T.data[2].e=1;
    T.data[3].i=2;
    T.data[3].j=0;
    T.data[3].e=-2;
    T.data[4].i=2;
    T.data[4].j=1;
    T.data[4].e=4;
    T.mu = 4;
    T.nu = 2;
    T.tu = 4;
    Rpos(&T);
    PrintRLSMatrix(T);

    RLSMatrix Q;
    MultSMatrix(M,T,&Q);
    PrintRLSMatrix(Q);


    return 0;
}



