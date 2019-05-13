#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "LinkQueue.h"
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20


typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef enum {True,False} Boolean;
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

Status InitALGraph(ALGraPtr *G);
Status CreateALGraph(ALGraph *G);
Status ShowADJList(ALGraph G);
int FirstAdjVex(ALGraph G, int x);
int NextAdjVex(ALGraph G, int x, int y);
Status visit(ElemType e);
Status ShortestPath(ALGraPtr G,int start,int end);
Status DFShortestPath(ALGraPtr G,int end,int *visited,LinkQueue *Q);






#endif // GRAPH_H_INCLUDED
