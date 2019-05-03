#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "MPNode.h"
/*
int main()
{
    MPlist p;
    p=CreateMPNode(1,2);
    CreateTestMP(p);
    PrintMP(p->hp,2);
    return 0;
}
*/

int main(){
    MPlist m,t;
    InitMP(&m);
    CreateTestMP(m);
    PrintMP(m->hp,2);
    //CopyMP(&t,m);
    printf("\n");
    DerivativeFisrtVar(&t,m);
    PrintMP(m->hp,2);
    printf("\n");
    PrintMP(t->hp,2);
    AddMP(t->hp,m->hp);
    printf("\n");
    PrintMP(t->hp,2);
    DestroyMP(t);

    return 0;
}
