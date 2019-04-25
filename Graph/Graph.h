#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
//------------Array(Adjacent Matrix)----------------------------
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20

typedef int VertexType; //the type of nodes
typedef int VRType; //the type of the arcs
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum,arcnum;
    GraphKind kind;
}MGraph,*MGraPtr;

Status InitMGraph(MGraPtr *G);
Status CreateMGraph(MGraph *G);
Status CreateMDG(MGraph *G);
Status CreateMDN(MGraph *G);
Status CreateMUDG(MGraph *G);
Status CreateMUDN(MGraph *G);
Status ShowAdjArray(MGraph G);

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




#endif // GRAPH_H_INCLUDED
