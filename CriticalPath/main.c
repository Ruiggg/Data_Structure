#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"


void testCriticalPath(){
/*
Sample:
0 13 24 LA 1 LB 6 LD 3 LF 4 LG 3 LI 1 AC 6 BC 2 DC 7 DE 8 DJ 6 FE 11 FH 5 GM 21 GH 10 IH 6 CE 8 HC 4 HJ 4 HK 9 KJ 9 JE 3 EM 10 JM 12 !! 2
*/
    ALGraph *G;
    InitALGraph(&G);
    CreateALGraph(G);
    //ShowADJList(*G);
    printf("\n\n\n\n");
    if(CriticalPath(G,printArc)!=OK) printf("\n\nError!\n");
}


int main()
{
    testCriticalPath();
    return 0;
}
