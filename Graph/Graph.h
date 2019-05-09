#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
//Queue:




//------------Array(Adjacent Matrix)----------------------------
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20


typedef enum {True,False} Boolean;
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
Status DFSGraph(ALGraph * p,Status(*visit)(ElemType e));
Status DFS(ALGraph *g,int *visited,int i,Status(*visit)(ElemType e));
Status visit(ElemType e);
Status BFS_II(ALGraph*G, Status(*visit)(ElemType e),int x);
Status BFS(ALGraph* G, Status(*visit)(ElemType e));


//Orthogonal List---for directed graph
//还以为自己多伟大，写了诗不敢递给她
typedef struct ArcBox {
    int tailvex,headvex;
    struct ArcBox * hlink,*tlink;
    //InfoType * info;
}ArcBox;
typedef struct VexNode {
    ElemType data;
    ArcBox *fisrtin,*firstout;
}VexNode;

typedef struct {
    VexNode xlist[MAX_VERTEX_NUM];
    int     vexnum,arcnum;
}OLGraph,* OLGraPtr;
Status InitOLGraph(OLGraPtr *P);
Status CreateOLGraph(OLGraph *G);
Status ShowOLGraph(OLGraph G);


//Adjacency Multilist --- undirected graph
typedef enum {unvisited,visited} VisitIf;
typedef struct EBox {
    VisitIf mark;
    int ivex,jvex;  //the index of the two nodes of the edge
    struct EBox * ilink,*jlink;
    //InfoType *info;
}EBox;
typedef struct VexBox {
    ElemType data;
    EBox    *firstedga;
}VexBox;
typedef struct {
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum,edgenum;
} AMLGraph,* AMLGraPtr;
Status InitAMLGraph(AMLGraPtr *G);
Status CreateAMLGraph(AMLGraph *G);
Status ShowAMLGraph(AMLGraph G);
Status ShowAMLGedge(AMLGraph G,int i,int *n); //i:the index of the node














#endif // GRAPH_H_INCLUDED
