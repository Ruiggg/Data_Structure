#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3
#define MAX_VERTEX_NUM 30
#define INFINITY 10000

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
typedef int InfoType;

//Adjacency List
typedef struct ArcNode {
    int adjvex; //The node that the arc points(store its position)
    struct ArcNode * nextarc;
    InfoType Info; //Eg:weight
}ArcNode;
typedef struct {
    int vexnum,edgenum,kind;
    struct {
        ElemType vertex;
        ArcNode *first;
    }v[MAX_VERTEX_NUM];
}ALGraph,*ALGraPtr;

Status CreateALGraph_Directed_OJ(ALGraph *G,int* start){

    scanf("%d",&(G->vexnum)); getchar(); scanf("%d",start); getchar();
    G->edgenum = 0;
    //input
    int h,t,w;
    char c='0';
    while(c!=EOF){
        char num[10]; int index = 1;
        num[0] = c;
        while((c=getchar())>='0' && c<='9') num[index++]=c;
        num[index]='\0';
        h = atoi(num);
        index = 0;
        while((c=getchar())>='0' && c<='9') num[index++]=c;
        num[index]='\0';
        t = atoi(num);
        index = 0;
        while((c=getchar())>='0' && c<='9') num[index++]=c;
        num[index]='\0';
        w = atoi(num);
        c=getchar();
        ArcNode * arc = (ArcNode *)malloc(sizeof(ArcNode));
        if(!arc) exit(OVERFLOW);
        G->edgenum++;
        arc->adjvex = t;
        arc->Info = w;
        arc->nextarc = G->v[h].first;
        G->v[h].first = arc;
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

Status InitDist(ALGraPtr G,int *dist,int start){
    dist[start] = 0;
    for(int i=1;i<=G->vexnum;i++) dist[i]=INFINITY;
    ArcNode *arc;
    for(arc=G->v[start].first;arc;arc=arc->nextarc) dist[arc->adjvex] = arc->Info;
    dist[start] = 0;
    return OK;
}

int findLeastDistNode(int *dist,int vexnum,int *IsDone){
    int leastNode = 0,leastdist = INFINITY,i;
    for(i=1;i<=vexnum;i++){
        if(IsDone[i]==False && dist[i]<leastdist){
            leastNode = i;
            leastdist = dist[i];
        }
    }
    return (leastdist==INFINITY)?-1:leastNode;
}

Status ChangeDist(ALGraPtr G,int *dist,int start,int node,int *IsDone){
    ArcNode * arc;
    for(arc=G->v[node].first;arc;arc=arc->nextarc){
        int adjv = arc->adjvex;
        if(IsDone[adjv]==False && dist[adjv]>dist[node]+arc->Info){
            dist[adjv] = dist[node] + arc->Info;
        }
    }
    return OK;
}

Status Dij_ALGraph(ALGraPtr G,int *dist,int start){
    int IsDone[MAX_VERTEX_NUM];
    for(int i=0;i<MAX_VERTEX_NUM;i++) IsDone[i]=False;
    IsDone[start] = True;
    InitDist(G,dist,start);

    int node = 1;
    while(node!=-1){
        node = findLeastDistNode(dist,G->vexnum,IsDone);
        if(node>0) IsDone[node] = True;
        if(node>0) ChangeDist(G,dist,start,node,IsDone);
    }
    return OK;
}

int main(){
    ALGraPtr G;
    int start;
    int dist[MAX_VERTEX_NUM];
    InitALGraph(&G);
    CreateALGraph_Directed_OJ(G,&start);
    Dij_ALGraph(G,dist,start);
    for(int i=1;i<=G->vexnum;i++){
        if(i!=start){
            printf("%d",dist[i]);
            if(i<G->vexnum) putchar(',');
        }
    }
}


/*
    for(int i=0;i<G->vexnum;i++)printf("%d:%d,",i+1,dist[i]);
*/
/*
4 1
1-2 1
1-4 3
2-3 1
3-4 2
3-1 5

*/
