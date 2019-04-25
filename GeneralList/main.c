#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "MPNode.h"

int main()
{
    MPlist p;
    p=CreateMPNode(1,2);
    CreateTestMP(p);
    PrintMP(p->hp,2);
    return 0;
}
