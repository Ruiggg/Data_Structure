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
    //InfoType *Info; //Eg:weight
}ArcNode;
typedef struct {
    int vexnum,edgenum,kind;
    struct {
        ElemType vertex;
        ArcNode *first;
    }v[MAX_VERTEX_NUM];
}ALGraph,*ALGraPtr;
Status DFSsearch(ALGraph *G,int start,int *visited);

Status DFSPath(ALGraph *G){
    int visited[MAX_VERTEX_NUM],i;
    for(i=0;i<MAX_VERTEX_NUM;i++) visited[i]=False;
    DFSsearch(G,0,visited);
    return OK;
}

Status DFSsearch(ALGraph *G,int start,int *visited){
    visited[start]=True;
    ArcNode * arc;
    for(arc=G->v[start].first; arc;arc=arc->nextarc){
        if(visited[arc->adjvex]==False)
            DFSsearch(G,arc->adjvex,visited);
    }
    printf("%c",G->v[start].vertex);
    return OK;
}

Status CreateALGraph_Directed_OJ(ALGraph *G){

    scanf("%d",&(G->vexnum)); getchar();
    G->edgenum = 0;
    //input
    int h,t; int num = 0;
    while(num < G->vexnum){
        char ch,c;
        scanf("%c",&ch); c = getchar();
        G->v[num].vertex = ch;

        while(c!='\n'){
            int adjv;
            scanf("%d",&adjv); c = getchar();
            ArcNode * arc = (ArcNode*)malloc(sizeof(ArcNode));
            if(!arc) exit(OVERFLOW);
            arc->adjvex = adjv;
            arc->nextarc = G->v[num].first;
            G->v[num].first = arc;
            G->edgenum ++;
        }
        num++;
    }
    return OK;
}

Status InitALGraph(ALGraPtr *G){
    (*G)=(ALGraPtr)malloc(sizeof(ALGraph));
    if(!(*G)) exit(OVERFLOW);
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        (*G)->v[i].first = NULL;
        (*G)->v[i].vertex = i;
    }
    return OK;
}




int main(){
    ALGraPtr G;
    InitALGraph(&G);
    G->kind = 0;
    CreateALGraph_Directed_OJ(G);
    //PrintAdjGraph(G,nodes);
    DFSPath(G);
    return 0;
}


