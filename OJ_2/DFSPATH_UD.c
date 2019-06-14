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
Status DFSsearch(ALGraph *G,int start,int target,int *found,int *visited,int k);

Status DFSPath(ALGraph *G,int a,int b,int k){
    int visited[MAX_VERTEX_NUM],i;
    for(i=0;i<MAX_VERTEX_NUM;i++) visited[i]=False;
    visited[a]=True; //visit

    int found = 0;//1: found
    ArcNode * arc;
    for(arc = G->v[a].first; arc && (!found) ; arc = arc->nextarc){
        if(arc->adjvex == b && k == 1){
            found = 1;
        }else if(k>=1){
            DFSsearch(G,arc->adjvex,b,&found,visited,k-1);
        }
    }
    if(found==0) {
        printf("no\n");
    }else
        printf("yes\n");
    return OK;
}

//visited[] records the nodes in the path
Status DFSsearch(ALGraph *G,int start,int target,int *found,int *visited,int k){
    visited[start]=True;
    if(start==target && k==0){
        *found = 1;
        return OK;
    }
    ArcNode * arc;
    for(arc=G->v[start].first; arc&&(!*found) ;arc=arc->nextarc){
        if(visited[arc->adjvex]==False){
            DFSsearch(G,arc->adjvex,target,found,visited,k-1);
        }
    }
    if(*found==0) visited[start] = False;
    return OK;
}

Status CreateALGraph_Directed_OJ(ALGraph *G,int *nodes){
    int top = 0;
    //scanf("%d",&(G->vexnum)); getchar(); //scanf("%d",&(G->edgenum));
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
        {
        //insert for another node
        ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
        if(!p) exit(OVERFLOW);
        p->adjvex = h;
        p->nextarc = NULL;
        ArcNode * arc = G->v[t].first;
        if(!arc){G->v[t].first=p; p->nextarc=NULL;}
        else{
            while(arc->nextarc && p->adjvex < arc->nextarc->adjvex) arc=arc->nextarc;
            if(!arc->nextarc){
                if(p->adjvex < arc->adjvex){
                    arc->nextarc = p;
                    p->nextarc = NULL;
                }
                else{
                    p->nextarc = arc;
                    G->v[t].first = p;
                }
            }else if(arc==G->v[t].first){
                if(p->adjvex > arc->adjvex){
                    p->nextarc = arc;
                    G->v[t].first = p;
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
        if(c=='\n' || c==EOF) break;
    }
    nodes[top] = -1;
    nodes[top+1] = top;
    return OK;
}

Status InitALGraph(ALGraPtr *G){
    (*G)=(ALGraPtr)malloc(sizeof(ALGraph));
    if(!(*G)) exit(OVERFLOW);
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
    G->kind = 2;
    int nodes[100],k,a,b;
    scanf("%d",&(G->vexnum)); getchar(); scanf("%d",&k); getchar();
    scanf("%d",&a); getchar(); scanf("%d",&b); getchar();
    CreateALGraph_Directed_OJ(G,nodes);
    //PrintAdjGraph(G,nodes);
    DFSPath(G,a,b,k);
    return 0;
}


