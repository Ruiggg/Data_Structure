#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"


int main()
{
    ALGraPtr G;
    InitALGraph(&G);
    CreateALGraph(G);
    ShowADJList(*G);
    return 0;
}
