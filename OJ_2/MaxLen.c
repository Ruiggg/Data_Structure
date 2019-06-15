#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3
#define MAX_VERTEX_NUM 30


typedef enum {True,False} Boolean;
typedef char VertexType; //the type of nodes
typedef int VRType; //the type of the arcs
typedef enum {DG,DN,UDG,UDN} GraphKind;
//0: directed graph
//1: directed network
//2: undirected graph
//3: undirected network
typedef char ElemType;
typedef int Status;

//Adjacency List
typedef struct ArcNode {
    int adjvex; //The node that the arc points(store its position)
    struct ArcNode * nextarc;
}ArcNode;
typedef struct {
    int vexnum,edgenum,kind;
    struct {
        ElemType vertex;
        ArcNode *first;
        int  MPL;   //max path length
    }v[MAX_VERTEX_NUM];
}ALGraph,*ALGraPtr;
Status DFSsearch(ALGraph *G,int start,int current,int length,int *visited);

Status DFSMaxPath(ALGraph *G,int *nodes){
    int visited[MAX_VERTEX_NUM],i;
    for(i=0;i<MAX_VERTEX_NUM;i++) visited[i]=False;
    for(i=0;i<G->vexnum;i++) DFSsearch(G,nodes[i],nodes[i],0,visited);
    for(i=0;i<G->vexnum;i++){
        printf("%d",G->v[nodes[i]].MPL);
        if(i<G->vexnum-1) printf(",");
    }
    printf("\n");
    return OK;
}

Status DFSsearch(ALGraph *G,int start,int current,int length,int *visited){
    visited[current]=True;
    if(length > G->v[start].MPL) G->v[start].MPL = length;
    ArcNode * arc;
    for(arc=G->v[current].first; arc ;arc=arc->nextarc){
        if(visited[arc->adjvex]==False)
            DFSsearch(G,start,arc->adjvex,length+1,visited);
    }
    visited[current]=False;
    return OK;
}

Status CreateALGraph_Directed_OJ(ALGraph *G,int *nodes){
    int top = 0;
    scanf("%d",&(G->vexnum)); getchar(); //scanf("%d",&(G->edgenum));
    G->edgenum = 0;
    //getchar();
    //initialize
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++){
        G->v[i].vertex = i;
        G->v[i].first  = NULL;
    }
    //input
    int h,t; int num = 0;
    while(1){
        scanf("%d",&h); getchar(); scanf("%d",&t); char c = getchar();
        G->edgenum++;
        int flagh=0,flagt=0;
        for(int i=0;i<top;i++){
            if(nodes[i]==h) flagh = 1;
            if(nodes[i]==t) flagt = 1;
        }
        if(flagh==0) nodes[top++] = h;
        if(flagt==0) nodes[top++] = t;
        num++;
        ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
        if(!p) exit(OVERFLOW);
        p->adjvex = t;
        p->nextarc = NULL;
        ArcNode * arc = G->v[h].first;
        if(!arc){G->v[h].first=p; p->nextarc=NULL;}
        else{
            while(arc->nextarc && p->adjvex < arc->nextarc->adjvex) arc=arc->nextarc;
            if(!arc->nextarc){
                if(p->adjvex < arc->adjvex){
                    arc->nextarc = p;
                    p->nextarc = NULL;
                }
                else{
                    p->nextarc = arc;
                    G->v[h].first = p;
                }
            }else if(arc==G->v[h].first){
                if(p->adjvex > arc->adjvex){
                    p->nextarc = arc;
                    G->v[h].first = p;
                }else{
                    p->nextarc = arc->nextarc;
                    arc->nextarc = p;
                }
            }else{
                p->nextarc=arc->nextarc;
                arc->nextarc=p;
            }
        }
        if(c=='\n') break;
    }
    nodes[top] = -1;
    nodes[top+1] = top;
    return OK;
}

Status InitALGraph(ALGraPtr *G){
    (*G)=(ALGraPtr)malloc(sizeof(ALGraph));
    if(!(*G)) exit(OVERFLOW);
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        (*G)->v[i].first = NULL;
        (*G)->v[i].vertex = i;
        (*G)->v[i].MPL = 0;
    }
    return OK;
}

int cmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}


int main(){
    ALGraPtr G;
    InitALGraph(&G);
    G->kind = 0;
    int nodes[100];
    CreateALGraph_Directed_OJ(G,nodes);
    qsort(nodes,G->vexnum,sizeof(int),cmp);
    //PrintAdjGraph(G,nodes);
    DFSMaxPath(G,nodes);
    return 0;
}


