#include <stdio.h>
#include <stdlib.h>
#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3

typedef char ElemType;
typedef int Status;
#define MAX_VERTEX_NUM 30
typedef enum {True,False} Boolean;
typedef char VertexType; //the type of nodes
typedef int VRType; //the type of the arcs
typedef enum {DG,DN,UDG,UDN} GraphKind;
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

Status InitALGraph(ALGraPtr *G){
    (*G)=(ALGraPtr)malloc(sizeof(ALGraph));
    if(!(*G)) exit(OVERFLOW);
    return OK;
}

Status CreateALGraph_Directed_OJ(ALGraph *G,int *nodes){
    int top = 0;
    scanf("%d",&(G->vexnum)); getchar(); scanf("%d",&(G->edgenum));
    getchar();
    //initialize
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++){
        G->v[i].vertex = i;
        G->v[i].first  = NULL;
    }
    //input
    int h,t; int num = 0;
    while(num < G->edgenum){
        scanf("%d",&h); getchar(); scanf("%d",&t); getchar();
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
    }
    nodes[top] = -1;
    nodes[top+1] = top;
    return OK;
}

int cmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}

Status PrintAdjGraph(ALGraPtr G,int *nodes){
    int n = 0;
    for(;nodes[n]!=-1;n++);
    qsort(nodes,n,sizeof(int),cmp);
    int i; int j=0;
    for(i=nodes[0];j<G->vexnum;i=nodes[++j]){
        printf("%d",G->v[i].vertex);
        if(G->v[i].first) putchar(' ');
        ArcNode *arc;
        for(arc=G->v[i].first;arc;arc=arc->nextarc){
            printf("%d",arc->adjvex);
            if(arc->nextarc) putchar(',');
        }
        //if(j!=n-1)
            putchar('\n');
    }
    return OK;
}

int main(){
    ALGraPtr G;
    InitALGraph(&G);
    G->kind = 0;
    int nodes[100];
    CreateALGraph_Directed_OJ(G,nodes);
    PrintAdjGraph(G,nodes);
    return OK;
}
