#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"
Status InitMGraph(MGraPtr *G){
    (*G) = (MGraPtr)malloc(sizeof(MGraph));
    if(!(*G)) exit(OVERFLOW);
    return OK;
}

Status CreateMGraph(MGraph *G){
    scanf("%d",&(G->kind));
    switch(G->kind){
        case DG: return CreateMDG(G); break;
        case DN: return CreateMDN(G); break;
        case UDG:return CreateMUDG(G); break;
        case UDN:return CreateMUDN(G); break;
        default : return ERROR;
    }
}

Status CreateMDG(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl;
        printf("Input an arc(i j): ");
        scanf("%d%d",&hd,&tl);
        G->arcs[hd][tl]=1;
    }
    return OK;
}

Status CreateMDN(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl,w;
        printf("Input an arc(i j w): ");
        scanf("%d%d%d",&hd,&tl,&w);
        G->arcs[hd][tl]=w;
    }
    return OK;
}

Status CreateMUDG(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl;
        printf("Input an arc(i j): ");
        scanf("%d%d",&hd,&tl);
        G->arcs[hd][tl]=G->arcs[tl][hd]=1;
    }
    return OK;
}

Status CreateMUDN(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl,w;
        printf("Input an arc(i j w): ");
        scanf("%d%d%d",&hd,&tl,&w);
        G->arcs[hd][tl]=G->arcs[tl][hd]==w;
    }
    return OK;
}

Status ShowAdjArray(MGraph G){
    int i,j;
    for(i=0;i<G.vexnum;i++){
        for(j=0;j<G.vexnum;j++){
            printf("%6d",G.arcs[i][j]);
        }
        printf("\n");
    }
    return OK;
}

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
            p->adjvex = h-'A';
            p->nextarc = G->v[t-'A'].first;
            G->v[t-'A'].first = p;
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



















