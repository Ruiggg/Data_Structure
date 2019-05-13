#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"
#include "LinkQueue.h"

//test:
//2 9 12 AB AC BC AD AG DE DF EF FH HI GI GH 1 1 2 4

Status InitALGraph(ALGraPtr *G){
    (*G)=(ALGraPtr)malloc(sizeof(ALGraph));
    if(!(*G)) exit(OVERFLOW);
    return OK;
}

Status CreateALGraph(ALGraph *G){
    printf("Input kind, vexnum and edgenum (kind vn en): ");
    scanf("%d%d%d",&(G->kind),&(G->vexnum),&(G->edgenum));
    getchar();
    //initialize
    int i;
    for(i=0;i<G->vexnum;i++){
        G->v[i].vertex = 'A'+i;
        G->v[i].first  = NULL;
    }
    //input
    char h,t;
    printf("Input edge x-->y (x y): ");
    scanf("%c%c",&h,&t);
    getchar();
    while(h>='A'&&h<='Z'&&t>='A'&&t<='Z'){
        ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
        if(!p) exit(OVERFLOW);
        p->adjvex = t-'A';
        p->nextarc = G->v[h-'A'].first;
        G->v[h-'A'].first = p;
        //
        if(G->kind == UDG || G->kind==UDN){//undirected graph
            ArcNode *q = (ArcNode*)malloc(sizeof(ArcNode));
            if(!q)  exit(OVERFLOW);
            q->adjvex = h-'A';
            q->nextarc = G->v[t-'A'].first;
            G->v[t-'A'].first = q;
        }
        printf("Input edge x-->y (x y): ");
        scanf("%c%c",&h,&t);
        getchar();
    }
    return OK;
}

Status ShowADJList(ALGraph G){
    int i;
    for(i=0;i<G.vexnum;i++){
        printf("%d: %c--> ",i,G.v[i].vertex);
        ArcNode* p = G.v[i].first;
        while(p){
            printf("%d",p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
    return OK;
}

int FirstAdjVex(ALGraph G, int x){
    //return the 1st node adjacent to node x(0-vexnum-1)
    if(x<0 || x>=G.vexnum)  return -1;
    ArcNode *p = G.v[x].first;
    if(p)   return p->adjvex;
    else return -1;
}

int NextAdjVex(ALGraph G, int x, int y){
    //return <x,y>'s next z s.t (s,z)
    if(x<0||x>=G.vexnum)    return -1;
    if(y<0||y>=G.vexnum)    return -1;
    ArcNode *p = G.v[x].first;
    while(p && p->adjvex!=y) p=p->nextarc;
    if(p && p->nextarc) return p->adjvex;
    else return -1;
}

Status visit(ElemType e){
    printf("%4c",e);
    return OK;
}

Status ShortestPath(ALGraPtr G,int start,int end){
    //check input:
    if(start<0||start>=G->vexnum||end<0||end>=G->vexnum) return ERROR;
    LinkQueue *Q;
    InitQueue(&Q);
    EnQueue(Q,start);

    int visited[G->vexnum];
    int i;
    for(i=0;i<G->vexnum;i++) visited[i]=False;

    visited[start] = True;//onlu when false that the node can be enqueued to the linkqueue
    DFShortestPath(G,end,visited,Q);
    return OK;
}


Status DFShortestPath(ALGraPtr G,int end,int *visited,LinkQueue *Q){
    int flag = 0;
    while(flag==0){
        int e;
        DeQueue(Q,&e);
        ArcNode *arc = G->v[Q->head->data].first;
        for(;arc;arc = arc->nextarc){
            if(visited[arc->adjvex]==False){
                EnQueue(Q,arc->adjvex);
                visited[arc->adjvex] = True;
                if(end==arc->adjvex) {flag=1;break;}
            }
        }
    }

    int simpleStack[G->vexnum],i=0;
    QueuePtr p = Q->rear;
    while(p->prior){
        simpleStack[i++] = p->data;
        p = p->prior;
    }
    //print the path
    for(;i>0;--i)
        printf("%4c",G->v[simpleStack[i-1]].vertex);
    return OK;
}








