#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "OLMatrix.h"

int main(){
    CrossList M,N;
    CreateSMatrix_OL(&M);
    PrintSMatrix_OL(M);
    CreateSMatrix_OL(&N);
    PrintSMatrix_OL(N);
    AddOLMatrix(&M,N);
    PrintSMatrix_OL(M);
    return 0;
}
