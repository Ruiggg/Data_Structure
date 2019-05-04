#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "TSMatrix.h"

int main()
{
    TSMatrix m,t;
    CreateTestTSMatrix(&m);
    PrintSMatrix(&m);
    //PrintTSArray(&m);
    printf("After transposition: \n");
    FastTransposeTSMatrix(&t,&m);
    PrintSMatrix(&t);
    //PrintTSArray(&t);
    return 0;
}

