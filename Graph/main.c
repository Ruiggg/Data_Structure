#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"


int main()
{
    AMLGraPtr G;
    InitAMLGraph(&G);
    CreateAMLGraph(G);
    ShowAMLGraph(*G);
    int i;
    for(i=0;i<G->vexnum;i++){
        int num;
        ShowAMLGedge(*G,i,&num);
        printf("edges' number adjacent to node %c is %d.\n",G->adjmulist[i].data,num);
    }
    return 0;
}
