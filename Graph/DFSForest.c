#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"
#include "CSTree.h"

CSTree CreateCSNode(ElemType data,CSTree firstchild,CSTree nextsibling){
    CSTree p = (CSTree)malloc(sizeof(CSNode));
    if(!p) return NULL;
    p->data = data;
    p->firstchild = firstchild;
    p->nextsibling = nextsibling;
    return p;
}

CSTree DFSForest(ALGraph *G){
    CSTree p;       //new created node
    CSTree q;       //former root
    CSTree t=NULL;  //node of the final bitree
    int visited[G->vexnum];
    for(int i=0;i<G->vexnum;i++) visited[i]=False;
    for(int i=0;i<G->vexnum;i++)
        if(visited[i]==False){
            if(!(p=CreateCSNode(G->v[i].vertex,NULL,NULL))) return ERROR;
            if(!t)  t = p;                  //if it is the first
            else    q->nextsibling = p;     //link p to the former root
            q = p;                          //renew the q(former root)
            DFSTree(G,i,p,visited);         //bulid a tree whose root is p
        }
    return t;
}

//bulid a tree whose root is p---in graph is i
Status DFSTree(ALGraPtr G,int i,CSTree p,int *visited){
    if(!p || i<0 || i>=G->vexnum || !G) return ERROR;
    CSTree p1;  //new created
    CSTree q1;  //former node
    visited[i] = True;          //first change the visited[]
    ArcNode * arc;
    for(arc = G->v[i].first ; arc ; arc = arc->nextarc){
        int pos = arc->adjvex;
        if(visited[pos] == False){
            CSTree p1 = CreateCSNode(G->v[pos].vertex,NULL,NULL);
            if(!p1) exit(OVERFLOW);
            if(!(p->firstchild)) p->firstchild = p1;
            else q1->nextsibling = p1;
            q1 = p1;
            DFSTree(G,pos,p1,visited);
        }//if
    }//for
    return OK;
}


Status PreOrderTraverse(CSTree T,Status(*visit)(ElemType e)){
    if(T){
        if(visit(T->data))
            if(PreOrderTraverse(T->firstchild,visit))
                if(PreOrderTraverse(T->nextsibling,visit))
                    return OK;
        return ERROR;
    }else return OK;
}

Status InOrderTraverse(CSTree T,Status(*visit)(ElemType e)){
    if(T){
        if(InOrderTraverse(T->firstchild,visit))
            if(visit(T->data))
                if(InOrderTraverse(T->nextsibling,visit))
                    return OK;
        return ERROR;
    }else return OK;
}


