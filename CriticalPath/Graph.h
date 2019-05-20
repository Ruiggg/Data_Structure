#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 30


typedef int InfoType;
typedef enum {True,False} Boolean;
typedef int VertexType; //the type of nodes
typedef int VRType; //the type of the arcs
typedef enum {DG,DN,UDG,UDN} GraphKind;
//0: directed graph
//1: directed network
//2: undirected graph
//3: undirected network





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

Status InitALGraph(ALGraPtr *G);
Status CreateALGraph(ALGraph *G);
Status ShowADJList(ALGraph G);
Status printArc(ElemType e1,ElemType e2);
Status CriticalPath(ALGraph *G,Status(*visit)(ElemType e1,ElemType e2));
Status push(int e,int *stack,int *top);
void FindIndegree(ALGraPtr g,int *indegree);
Status TopologicalSort(ALGraPtr g,Status(*visit)(int e,int *stack,int *top),int *stack,int top,int *ve);





#endif // GRAPH_H_INCLUDED
