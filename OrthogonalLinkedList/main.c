#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "SMatrix_OL.h"

//2 2 2  0 0 -1  1 1 2     2 2 4  0 0 1  0 1 1  1 0 1  1 1 5
//-1 0   +   1 1
//0 2        1 5
void testCreatePrint(){
    CrossList M,N;
    CreateSMatrix_OL(&M);
    printf("\n");
    PrintSMatrix_OL(&M);
    CreateSMatrix_OL(&N);
    printf("\n");
    PrintSMatrix_OL(&N);
    AddSMatrix_OL(&M,&N);
    printf("\n");
    PrintSMatrix_OL(&M);
    printf("\n");
    Check_TraverseCol(&M);
    printf("\n---------------------------------\n");
    Check_TraverseRow(&M);
}


void OJtest(){
    CrossList M,N;
    CreateSMatrix_OJ(&M,&N);
    PrintSMatrix_OL(&M);
    PrintSMatrix_OL(&N);
    AddSMatrix_OL(&M,&N);
    OJ_Print_SMatrix_OL(&M);
    printf("\n");
    PrintSMatrix_OL(&M);
    printf("\n");
    Check_TraverseCol(&M);
    printf("\n---------------------------------\n");
    Check_TraverseRow(&M);
    printf("\n");

}
int main()
{
    //testCreatePrint();
    OJtest();
    return 0;
}
