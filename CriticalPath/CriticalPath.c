#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"

Status printArc(ElemType e1,ElemType e2){
    printf(" (%c,%c) ",e1,e2);
    return OK;
}

Status CriticalPath(ALGraph *G,Status(*visit)(ElemType e1,ElemType e2)){
    int ve[G->vexnum];
    int vl[G->vexnum];
    int stack[G->vexnum],top=0;
    //initialize
    for(int i=0;i<G->vexnum;i++) ve[i]=0;
    //toposort calculate ve and push to the stack
    if(TopologicalSort(G,push,stack,top,ve)!=OK) return ERROR;
    //initilize
    for(int i=0;i<G->vexnum;i++) vl[i]=ve[G->vexnum-1];
    //calculate vl
    top = G->vexnum;
    while(top){
        ArcNode *arc;
        int pos = stack[--top];
        for(arc=G->v[pos].first ; arc ; arc=arc->nextarc){
            if(vl[arc->adjvex]-arc->Info < vl[pos]) vl[pos]=vl[arc->adjvex]-arc->Info;
        }//for
    }//while
    //cal every edge's ee and el and determine whether it is a critical activity
    for(int i=0;i<G->vexnum;i++){
        ArcNode *arc;
        for(arc=G->v[i].first; arc; arc=arc->nextarc){
            int ee = ve[i];
            //printf("ee(%c,%c): %2d\n",G->v[i].vertex,G->v[arc->adjvex].vertex,ee);
            int el = vl[arc->adjvex]-arc->Info;
            //printf("el(%c,%c): %2d\n",G->v[i].vertex,G->v[arc->adjvex].vertex,el);
            if(ee==el) visit(G->v[i].vertex,G->v[arc->adjvex].vertex);
        }//for
    }//for
    //show ve vl
    //for(int j=0;j<G->vexnum;j++) printf("%c:%d  ",G->v[j].vertex,ve[j]);
    //printf("\n");
    //for(int j=0;j<G->vexnum;j++) printf("%c:%d  ",G->v[j].vertex,vl[j]);
    return OK;
}










