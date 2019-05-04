#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "TSMatrix.h"

int main()
{
    TSMatrix m;
    CreateTestTSMatrix(&m);
    PrintSMatrix(m);
    return 0;
}
