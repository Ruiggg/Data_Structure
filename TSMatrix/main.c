#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "TSMatrix.h"

/*
int main()
{
    TSMatrix m,t;
    CreateTestTSMatrix(&m);
    PrintSMatrix(&m);
    PrintTSArray(&m);
    printf("After transposition: \n");
    FastTransposeTSMatrix(&t,&m);

    PrintSMatrix(&t);
    //PrintTSArray(&t);
    return 0;
}
*/
// 1 0  *  2 1
// 0 -1    -1 2
//2 2 0 0 1 1 1 -1 -1 -1 1 2 2 0 0 2 0 1 1 1 0 -1 1 1 2 -1 -1 1
void testRLSMatrix(void){
    RLSMatrix t,s,d;
    CreateRLSMatrix(&t);
    CreateRLSMatrix(&s);
    printf("\n----------------------------------------\n");
    printf("Matrix t:\n");
    PrintRLSMatrix(&t);
    printf("Matrix s:\n");
    PrintRLSMatrix(&s);
    MultRLSMatrix(&d,&t,&s);
    printf("Matrix d:\n");
    PrintRLSMatrix(&d);
}

int main(){
    testRLSMatrix();
    return 0;
}

