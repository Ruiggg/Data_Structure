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

typedef struct DGraph {
    int vexnum;
    int s[MAX_VERTEX_NUM];
    int fst[MAX_VERTEX_NUM];
    int lst[MAX_VERTEX_NUM];
} DGraph,*DGraPtr;


void FindIndegree(DGraPtr g,int *indegree){
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++) indegree[i]=0;//initialize
    for(i=1;i<=g->vexnum;i++){
        int succ[MAX_VERTEX_NUM];
        int numOfSucc = findSucc(g,i,succ);
        for(int i=0;i<numOfSucc;i++){
            indegree[succ[i]]++;
        }
    }
}

int findSucc(DGraPtr g,int vex,int *succ){
    if(vex<=0) return -1;
    int top = 0;
    for(;top<MAX_VERTEX_NUM;top++)  succ[top] = 0;  //init
    top = 0;
    int start = g->fst[vex];
    int end   = g->lst[vex];
    for(int i=start;i<end;i++){
        //check if it is in succ-array
        int flag  = 0;
        int sv = g->s[i];
        for(int j=0;j<top;j++){
            if(succ[j]==sv) flag = 1;
        }
        if(!flag) succ[top++] = sv;
    }
    return top;
}

Status TopologicalSort(DGraPtr g){
    int indegree[MAX_VERTEX_NUM];                   //index means the index of node in g->v
    FindIndegree(g,indegree);                       //find the initial in-degree of each node
    int simplestack[MAX_VERTEX_NUM],i,top=0,count=0;
    for(i=1;i<=g->vexnum;i++)
        if(indegree[i]==0) simplestack[top++]=i;    //find 0 indegree nodes
    while(top>0){
        int vex = simplestack[--top];               //pop a node in the stack
        count++;
        int succ[MAX_VERTEX_NUM];
        int numOfSuccOfVex = findSucc(g,vex,succ);
        if(numOfSuccOfVex<0) return ERROR;
        for(int j=0;j<numOfSuccOfVex;j++){
            int adjvex = succ[j];
            if( (--indegree[adjvex]) == 0) simplestack[top++]=adjvex;
        }
    }
    if(count<g->vexnum) return ERROR;
    else return OK;
}

Status InitDGraph(DGraPtr *g){
    (*g) = (DGraPtr)malloc(sizeof(DGraph));
    if(!(*g)) exit(OVERFLOW);
    (*g)->vexnum = 0;
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        (*g)->fst[i] = (*g)->lst[i] = (*g)->s[i] = 0;
    }
    return OK;
}

int main(void){
    DGraPtr g;
    InitDGraph(&g);
    scanf("%d",&(g->vexnum)); getchar();
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        scanf("%d",(g->s)+i); char c = getchar();
        if(c=='\n') break;
    }
    for(int i=0;i<=g->vexnum;i++){
        scanf("%d",(g->fst)+i); getchar();
    }
    for(int i=0;i<=g->vexnum;i++){
        scanf("%d",(g->lst)+i); getchar();
    }
    int hasCircle = TopologicalSort(g);
    if(hasCircle==ERROR) puts("yes");
    else puts("no");
    return 0;
}















