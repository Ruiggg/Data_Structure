#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"

Status PrintElemType(ElemType e){
    printf("%c ",e);
    return OK;
}

Status FindArticul(ALGraph *G,Status(*visit)(ElemType e)){
    //node 0 is the root
    int visited[G->vexnum];
    int low[G->vexnum];
    //initialize
    for(int i=0;i<G->vexnum;i++) visited[i]=0;
    int count = 1;  //node 0 is the 1st visited
    visited[0] = count;
    if(G->v[0].first){
        int v = G->v[0].first->adjvex;
        if(DFSArticulationPoint(G,v,visit,&count,visited,low)!=OK) return ERROR;
        if(count>=G->vexnum){
            ArcNode *arc = G->v[0].first->nextarc;
            for(;arc;arc=arc->nextarc){
                int v = arc->adjvex;
                if(visited[v]==0)
                    if(DFSArticulationPoint(G,v,visit,&count,visited,low)!=OK) return ERROR;
            }
        }else{
            visit(G->v[0].vertex);
        }
    }
    //examineArticul(G,low,visited);
    //printf("\ncount=%d\n",count);
    return OK;
}

Status DFSArticulationPoint(ALGraph*G,int v,Status(*visit)(ElemType e),int *count,int *visited,int *low){
    visited[v] = ++(*count);
    int min = visited[v];
    ArcNode * arc;
    for(arc=G->v[v].first;arc;arc=arc->nextarc){
        int index = arc->adjvex;
        if(visited[index]==0){
            if(DFSArticulationPoint(G,index,visit,count,visited,low)!=OK) return ERROR;
            if(low[index] >= visited[v])
                visit(G->v[v].vertex);
            if(low[index] < min) min = low[index];
        }else{  //the returning edge
            if(visited[index]<min)  //the reason for cmp is the node could be visited after v
                min = visited[index];
        }
    }
    low[v] = min;
    return OK;
}

Status examineArticul(ALGraph* G,int *low,int *visited){
    printf("\n\n-----------------------------------------\n");
    ShowADJList(*G);
    printf("\nlow:     ");
    for(int i=0;i<G->vexnum;i++) printf("%3d",low[i]);
    printf("\nvisited: ");
    for(int i=0;i<G->vexnum;i++) printf("%3d",visited[i]);
    return OK;
}

















