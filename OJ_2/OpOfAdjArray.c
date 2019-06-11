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

typedef char ElemType;
typedef int Status;


typedef enum {True,False} Boolean;
typedef int VertexType; //the type of nodes
typedef int VRType; //the type of the arcs
typedef enum {DG,DN,UDG,UDN} GraphKind;
//0: directed graph
//1: directed network
//2: undirected graph
//3: undirected network

typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum,arcnum;
    GraphKind kind;
}MGraph,*MGraPtr;

Status InitMGraph(MGraPtr *G){
    (*G) = (MGraPtr)malloc(sizeof(MGraph));
    if(!(*G)) exit(OVERFLOW);
    (*G)->arcnum = 0;
    (*G)->vexnum = 0;
    for(int i=0;i<MAX_VERTEX_NUM;i++) (*G)->vexs[i] = 0;
    for(int i=0;i<MAX_VERTEX_NUM;i++)
        for(int j=0;j<MAX_VERTEX_NUM;j++)
            (*G)->arcs[i][j] = 0;
    return OK;
}

int cmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}

Status ReadInput(MGraPtr G){
    int i = 0;
    scanf("%d",&(G->vexnum)); getchar();
    char c;
    while(c!='\n'){
        int h,t;
        scanf("%d",&h); c = getchar();
        scanf("%d",&t); c = getchar();
        G->arcs[h][t] = 1;
        G->arcnum ++;
        int flagh = 0,flagt = 0;
        for(int j=0;j<i;j++){
            if(h==G->vexs[j]) flagh = 1;
            if(t==G->vexs[j]) flagt = 1;
        }
        if(!flagh) G->vexs[i++] = h;
        if(!flagt) G->vexs[i++] = t;
    }
    qsort(G->vexs,i,sizeof(VertexType),cmp);
    //puts(""); for(int i=0;i<G->vexnum;i++) printf("%d ",G->vexs[i]); puts("");
    return OK;
}

Status DeleteNode(MGraPtr G,VertexType node){
    int i;
    for(i=0;i<G->vexnum;i++){
        if(G->vexs[i]==node) break;
    }
    if(i>=G->vexnum) return ERROR;
    for(int j=i;j<G->vexnum-1;j++){
        G->vexs[j] = G->vexs[j+1];
    }
    G->vexnum--;
    return OK;
}

Status AddNode(MGraPtr G,VertexType node){
    int pos = 0;
    for(;node>G->vexs[pos];pos++);
    for(int j=G->vexnum;j>pos;j--) G->vexs[j]=G->vexs[j-1];
    G->vexs[pos] = node;
    G->vexnum++;
    return OK;
}

Status DeleteArc(MGraPtr G,int h,int t){
    G->arcs[h][t] = 0;
    G->arcnum--;
    return OK;
}

Status AddArc(MGraPtr G,int h,int t){
    G->arcs[h][t] = 1;
    G->arcnum++;
    return OK;
}

Status ShowAdjArray(MGraPtr G){
    for(int i=0;i<G->vexnum;i++){
        for(int j=0;j<G->vexnum;j++){
            int h = G->vexs[i];
            int t = G->vexs[j];
            printf("%d",G->arcs[h][t]);
            if(j<G->vexnum-1) putchar(',');
        }
        puts("");
    }
    return OK;
}

int main(){
    MGraPtr G;
    InitMGraph(&G);
    ReadInput(G);
    //puts("----------------------------");
    //ShowAdjArray(G);
    //puts("----------------------------");
    while(1){
        char c1 = getchar(); if(c1==EOF) break;
        char c2 = getchar();
        if(c1=='I'&&c2=='V'){
            getchar(); int node; scanf("%d",&node);
            getchar(); getchar();
            AddNode(G,node);
        }else if(c1=='I'&&c2=='A'){
            getchar(); int h,t; scanf("%d",&h); getchar();
            scanf("%d",&t); getchar(); getchar();
            AddArc(G,h,t);
        }else if(c1=='D'&&c2=='V'){
            getchar(); int node; scanf("%d",&node);
            getchar(); getchar();
            DeleteNode(G,node);
        }else if(c1=='D'&&c2=='A'){
            getchar(); int h,t; scanf("%d",&h); getchar();
            scanf("%d",&t); getchar(); getchar();
            DeleteArc(G,h,t);
        }
        //puts(""); ShowAdjArray(G); puts("");
    }
    ShowAdjArray(G);
}

