#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"
#include "Kosaraju.h"

Status ConnectedComponent(OLGraph *G){
    int visited[G->vexnum];
    int finished[G->vexnum],top=0;    //stack
    //initialize
    for(int i=0;i<G->vexnum;i++) visited[i] = False;
    //DFS and change finished-stack
    for(int i=0;i<G->vexnum;i++)
        if(visited[i]==False) DFS_KOS(G,&top,i,visited,finished);
    //initialize
    for(int i=0;i<G->vexnum;i++) visited[i] = False;
    //reverse DFS
    int k = 1;
    for(int j=G->vexnum-1;j>=0;j--){
        int v = finished[j];
        if(visited[v]==False){
            printf("\nThe %3d-th component: ",k++);
            ReverseDFS_KOS(G,v,visited,visit);
            printf("\n");
        }//if
    }//for
    return OK;
}

Status DFS_KOS(OLGraph *G,int *top,int i,int *visited,int *finished){
    visited[i] = True;
    ArcBox * arc;
    for(arc=G->xlist[i].firstout;arc;arc=arc->tlink){
        if(visited[arc->headvex]==False)
            DFS_KOS(G,top,arc->headvex,visited,finished);
    }
    finished[(*top)++] = i;
    return OK;
}

Status ReverseDFS_KOS(OLGraph *G,int v,int *visited,Status(*visit)(ElemType e)){
    visited[v] = True;
    visit(G->xlist[v].data);
    ArcBox *arc;
    for(arc=G->xlist[v].fisrtin;arc;arc=arc->hlink){
        if(visited[arc->tailvex]==False)
            ReverseDFS_KOS(G,arc->tailvex,visited,visit);
    }
    return OK;
}










































