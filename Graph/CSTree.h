#ifndef CSTREE_H_INCLUDED
#define CSTREE_H_INCLUDED

typedef struct cstree {
    ElemType data;
    struct cstree * firstchild,*nextsibling;
}CSNode, *CSTree;

CSTree CreateCSNode(ElemType data,CSTree firstchild,CSTree nextsibling);
CSTree DFSForest(ALGraph *G);
Status DFSTree(ALGraPtr G,int i,CSTree p,int *visited);
Status PreOrderTraverse(CSTree T,Status(*visit)(ElemType e));
Status InOrderTraverse(CSTree T,Status(*visit)(ElemType e));

#endif // CSTREE_H_INCLUDED
