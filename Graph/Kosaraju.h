#ifndef KOSARAJU_H_INCLUDED
#define KOSARAJU_H_INCLUDED


Status ConnectedComponent(OLGraph *G);
Status DFS_KOS(OLGraph *G,int *top,int i,int *visited,int *finished);
Status ReverseDFS_KOS(OLGraph *G,int v,int *visited,Status(*visit)(ElemType e));





#endif // KOSARAJU_H_INCLUDED
