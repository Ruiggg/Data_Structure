#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"



Status InitALGraph(ALGraPtr *G){
    (*G)=(ALGraPtr)malloc(sizeof(ALGraph));
    if(!(*G)) exit(OVERFLOW);
    for(int i=0;i<MAX_VERTEX_NUM;i++) (*G)->v[i].first = NULL,(*G)->v[i].vertex = '\0';
    return OK;
}

Status CreateALGraph(ALGraph *G){
    printf("Input kind, vexnum and edgenum (kind vn en): ");
    scanf("%d%d%d",&(G->kind),&(G->vexnum),&(G->edgenum));
    getchar();
    //initialize
    int i;
    for(i=0;i<26;i++){
        G->v[i].vertex = 'A'+i;
        G->v[i].first  = NULL;
    }
    //input
    char h,t; int weight;
    printf("Input edge x-->y (x y w): ");
    scanf("%c%c%d",&h,&t,&weight);
    getchar();
    //int index = 0;
    while(h>='A'&&h<='Z'&&t>='A'&&t<='Z'){
        ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
        if(!p) exit(OVERFLOW);
        p->adjvex = t-'A';
        p->nextarc = G->v[h-'A'].first;
        p->Info = weight;
        G->v[h-'A'].first = p;
        //
        if(G->kind == UDG || G->kind==UDN){//undirected graph
            ArcNode *q = (ArcNode*)malloc(sizeof(ArcNode));
            if(!q)  exit(OVERFLOW);
            q->adjvex = h-'A';
            q->nextarc = G->v[t-'A'].first;
            q->Info = weight;
            G->v[t-'A'].first = q;
        }
        printf("Input edge x-->y (x y w): ");
        scanf("%c%c%d",&h,&t,&weight);
        getchar();
    }
    return OK;
}

Status ShowADJList(ALGraph G){
    printf("\n");
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++){
        printf("%2d: %c--> ",i,G.v[i].vertex);
        ArcNode* p = G.v[i].first;
        while(p){
            printf("(%c,%d) ",G.v[p->adjvex].vertex,p->Info);
            p = p->nextarc;
        }
        printf("\n");
    }
    return OK;
}
