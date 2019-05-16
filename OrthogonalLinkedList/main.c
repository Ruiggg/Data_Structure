#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "SMatrix_OL.h"


void testCreatePrint(){
    CrossList M;
    CreateSMatrix_OL(&M);
    PrintSMatrix_OL(&M);
}

int main()
{
    testCreatePrint();
    return 0;
}
