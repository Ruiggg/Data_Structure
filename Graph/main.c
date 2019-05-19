#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"
#include "CSTree.h"
#include "Kosaraju.h"

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
    int kind = TopologicalSort(g);
    if(kind==ERROR)
        printf("\nThere exists loop.\n");
    else
        printf("\nNo loop.\n");
}


void testMGraph(){
    MGraPtr G;
    InitMGraph(&G);
    CreateMGraph(G);
    ShowAdjArray(*G);
}

void testALGraph(){
    ALGraph *G;
    InitALGraph(&G);
    CreateALGraph(G);
    ShowADJList(*G);
}

void testCSForest(){
//2 9 10 AB BE AD AC BC EG DF CF FH HI
    ALGraph *G;
    InitALGraph(&G);
    CreateALGraph(G);
    ShowADJList(*G);
    printf("\n----------------------------------------------------\n");
    CSTree t = DFSForest(G);
    printf("Pre: ");
    PreOrderTraverse(t,visit);
    printf("\nIn: ");
    InOrderTraverse(t,visit);
}

void testKosaraju(){
//6 8 AC CD DA AB CF EB BF FE
//6 11 BA FA EA DF DE BD CB CF DC FB FE
    OLGraPtr G;
    InitOLGraph(&G);
    CreateOLGraph(G);
    ConnectedComponent(G);
}

int main(void){
    //testTopologicalSort();
    //testMGraph();
    //testCSForest();
    testKosaraju();
    return 0;
}



