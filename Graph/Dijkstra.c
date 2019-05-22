#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"

Status ShowDist(int *dist,int n){
    printf("\ndist:  ");
    for(int i=0;i<n;i++) printf("%d  ",dist[i]);
    printf("\n");
    return OK;
}

Status ShortestPath_DIJ(MGraph* G,int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int v0){
    if(v0<0||v0>=G->vexnum) return ERROR;

    int dist[MAX_VERTEX_NUM];       //record l(z)
    int finish[MAX_VERTEX_NUM];     //record S
    //initialize
    for(int i=0;i<MAX_VERTEX_NUM;i++) finish[i] = False;

    for(int i=0;i<MAX_VERTEX_NUM;i++)
        dist[i]=G->arcs[v0][i];
    //ShowDist(dist,G->vexnum);
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        for(int j=0;j<MAX_VERTEX_NUM;j++){
            P[i][j] = False;
        }
        if(dist[i] < INFINITY){
            //printf("\n*********\ndist[%d]-INF=%d-%d\n********\n",i,dist[i],INFINITY);
            P[i][v0] = True;
            P[i][i] = True;
        }
    }
    //ShowP(G,P,v0);

    dist[v0] = 0;
    finish[v0] = True;              //add v0 to S
    int count = 1;

    while(count<G->vexnum){
        int min=INFINITY,min_i=-1;
        //find the minimum dist[]
        for(int i=0;i<MAX_VERTEX_NUM;i++){
            if(finish[i]==False && dist[i]<min){
                min_i = i;
                min = dist[i];
            }//if
        }//for
        if(min_i==-1) return ERROR;
        finish[min_i] = True;       //add it to S
        count++;
        //printf("\nNore: %d add to S \n",min_i);
        //change dist[]
        for(int i=0;i<MAX_VERTEX_NUM;i++){
            if(finish[i]==False && dist[i]>dist[min_i]+G->arcs[min_i][i]){
                dist[i] = dist[min_i]+G->arcs[min_i][i];
                //ShowDist(dist,G->vexnum);
                for(int j=0;j<MAX_VERTEX_NUM;j++) P[i][j] = P[min_i][j];    //change the path
                P[i][i] = True;

                //printf("\n------\ni=%d\n",i);
                //ShowP(G,P,v0);
                //printf("-----------\n");
            }//if
        }//for
    }//while
    return OK;
}

Status ShowP(MGraph*G, int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM],int v0){
    printf("\n");
    for(int i=0;i<G->vexnum;i++){
        printf("From %c to %c: ",G->vexs[v0],G->vexs[i]);
        for(int j=0;j<G->vexnum;j++){
            if(P[i][j]==True)
                printf("%3c",G->vexs[j]);
        }
        printf("\n");
    }
    return OK;
}

//P[i] = the prior node of the node i in the shortest path whose inner nodes are in S
//P should be initialize in the function
Status ShortestPath_DIJ_II(MGraph *G,int P[MAX_VERTEX_NUM],int v0){
    if(v0<0 || v0>=MAX_VERTEX_NUM) return ERROR;
    //main data structure:
    int finish[MAX_VERTEX_NUM];     //S
    int dist[MAX_VERTEX_NUM];       //the length from v0 to node i using nodes in S as inner nodes
    //initialize
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        finish[i] = False;
        dist[i] = G->arcs[v0][i];
        P[i] = (i==v0)?-2:(dist[i]<INFINITY)?v0:-1;
    }
    //do the algorithm
    finish[v0] = True;      //add v0 to S
    int count = 1;
    while(count < G->vexnum){
        //find the min-dist
        int min_i = -1, min = INFINITY;
        for(int i=0;i<MAX_VERTEX_NUM;i++){
            if(finish[i]==False && dist[i]<min){
                min_i = i;
                min = dist[i];
            }//if
        }//for
        if(min_i==-1) return ERROR;
        //change S and dist
        finish[min_i] = True;
        for(int i=0;i<MAX_VERTEX_NUM;i++){
            if(finish[i]==False && dist[i]>dist[min_i]+G->arcs[min_i][i]){
                dist[i] = dist[min_i] + G->arcs[min_i][i];
                P[i] = min_i;
                //printf("\n--------------------------------\n");
                //for(int j=0;j<G->vexnum;j++) printf("%2d",P[j]);
            }//if
        }//for

        count++;
    }

    return OK;
}


Status ShowP_II(MGraph *G,int P[MAX_VERTEX_NUM],int v0){
    printf("\n\n");
    int simpleStack[MAX_VERTEX_NUM],top=0;
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        if(P[i]>=0){
            printf("Shoertest Path from %c to %c: ",G->vexs[v0],G->vexs[i]);
            simpleStack[top++] = i;
            for(int j=i;P[j]!=-2;j=P[j]) simpleStack[top++] = P[j];
            //print path
            for(--top;top>=0;top--) printf("%3c",G->vexs[simpleStack[top]]);
            printf("\n");
            top = 0;
        }//if
    }//for
    return OK;
}











