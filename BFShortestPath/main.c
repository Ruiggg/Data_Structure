#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"

int main()
{
    ALGraPtr g;
    InitALGraph(&g);
    CreateALGraph(g);
    ShowADJList(*g);
    printf("\n");
    printf("Enter start and end: ");
    int start,end;
    scanf("%d%d",&start,&end);
    ShortestPath(g,start,end);
    return 0;
}
