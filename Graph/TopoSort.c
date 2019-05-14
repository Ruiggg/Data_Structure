#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"
#include "LinkQueue.h"
//base on ALGraph

//int indegree[MAX_VERTEX_NUM];

void FindIndegree(ALGraPtr g,int *indegree){
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++) indegree[i]=0;//initialize
    for(i=0;i<g->vexnum;i++){
        ArcNode * arc = g->v[i].first;
        while(arc){
            indegree[arc->adjvex]++;
            arc=arc->nextarc;
        }//while
    }//for
}

Status TopologicalSort(ALGraPtr g){
    int indegree[MAX_VERTEX_NUM];//index means the index of node in g->v
    FindIndegree(g,indegree);//find the initial in-degree of each node
    int simplestack[g->vexnum],i,top=0,count=0;
    for(i=0;i<g->vexnum;i++)
        if(indegree[i]==0) simplestack[top++]=i; //find 0 indegree nodes
    while(top>0){
        int vex = simplestack[--top];//pop a node in the stack
        count++;
        visit(g->v[vex].vertex);
        ArcNode * edge;
        for(edge=g->v[vex].first;edge;edge=edge->nextarc){
            if( (--indegree[edge->adjvex]) == 0) simplestack[top++]=edge->adjvex;
        }
    }
    if(count<g->vexnum) return ERROR;
    else return OK;
}

