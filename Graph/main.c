#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"

/*
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
*/
/*
int main(){
    ALGraPtr g;
    InitALGraph(&g);
    CreateALGraph(g);
    ShowADJList(*g);
    //DFSGraph(g,visit);
    BFS_II(g,visit,0);
    printf("\n");
    char path[20];
    path[0] = '\0';
    //path[1] = 'a';
    //path[2] = 'b';
    //path[3] = '\0';
    //printf("%s\n",path);
    DFSPath(g,1,5,path);
    printf("%s\n",path);
    return 0;
}
*/


void testTopologicalSort(void){
    ALGraPtr g;
    InitALGraph(&g);
    CreateALGraph(g);
    TopologicalSort(g);
}

int main(void){
    testTopologicalSort();
    return 0;
}



