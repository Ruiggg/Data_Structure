#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Graph.h"
Status InitMGraph(MGraPtr *G){
    (*G) = (MGraPtr)malloc(sizeof(MGraph));
    if(!(*G)) exit(OVERFLOW);
    return OK;
}

Status CreateMGraph(MGraph *G){
    scanf("%d",&(G->kind));
    switch(G->kind){
        case DG: return CreateMDG(G); break;
        case DN: return CreateMDN(G); break;
        case UDG:return CreateMUDG(G); break;
        case UDN:return CreateMUDN(G); break;
        default : return ERROR;
    }
}

Status CreateMDG(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl;
        printf("Input an arc(i j): ");
        scanf("%d%d",&hd,&tl);
        G->arcs[hd][tl]=1;
    }
    return OK;
}

Status CreateMDN(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl,w;
        printf("Input an arc(i j w): ");
        scanf("%d%d%d",&hd,&tl,&w);
        G->arcs[hd][tl]=w;
    }
    return OK;
}

Status CreateMUDG(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl;
        printf("Input an arc(i j): ");
        scanf("%d%d",&hd,&tl);
        G->arcs[hd][tl]=G->arcs[tl][hd]=1;
    }
    return OK;
}

Status CreateMUDN(MGraph *G){
    printf("Enter vexnum,arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    //initialize
    int i,j;
    for(i=0;i<G->vexnum;i++) scanf("%d",&(G->vexs[i]));
    for(i=0;j<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->arcs[i][j]=0;
    //input the adjacent array
    for(i=0;i<G->arcnum;i++){
        int hd,tl,w;
        printf("Input an arc(i j w): ");
        scanf("%d%d%d",&hd,&tl,&w);
        G->arcs[hd][tl]=G->arcs[tl][hd]==w;
    }
    return OK;
}

Status ShowAdjArray(MGraph G){
    int i,j;
    for(i=0;i<G.vexnum;i++){
        for(j=0;j<G.vexnum;j++){
            printf("%6d",G.arcs[i][j]);
        }
        printf("\n");
    }
    return OK;
}

Status InitALGraph(ALGraPtr *G){
    (*G)=(ALGraPtr)malloc(sizeof(ALGraph));
    if(!(*G)) exit(OVERFLOW);
    return OK;
}

Status CreateALGraph(ALGraph *G){
    printf("Input kind, vexnum and edgenum (kind vn en): ");
    scanf("%d%d%d",&(G->kind),&(G->vexnum),&(G->edgenum));
    getchar();
    //initialize
    int i;
    for(i=0;i<G->vexnum;i++){
        G->v[i].vertex = 'A'+i;
        G->v[i].first  = NULL;
    }
    //input
    char h,t;
    printf("Input edge x-->y (x y): ");
    scanf("%c%c",&h,&t);
    getchar();
    while(h>='A'&&h<='Z'&&t>='A'&&t<='Z'){
        ArcNode * p = (ArcNode*)malloc(sizeof(ArcNode));
        if(!p) exit(OVERFLOW);
        p->adjvex = t-'A';
        p->nextarc = G->v[h-'A'].first;
        G->v[h-'A'].first = p;
        //
        if(G->kind == UDG || G->kind==UDN){//undirected graph
            ArcNode *q = (ArcNode*)malloc(sizeof(ArcNode));
            if(!q)  exit(OVERFLOW);
            p->adjvex = h-'A';
            p->nextarc = G->v[t-'A'].first;
            G->v[t-'A'].first = p;
        }
        printf("Input edge x-->y (x y): ");
        scanf("%c%c",&h,&t);
        getchar();
    }
    return OK;
}

Status ShowADJList(ALGraph G){
    int i;
    for(i=0;i<G.vexnum;i++){
        printf("%d: %c--> ",i,G.v[i].vertex);
        ArcNode* p = G.v[i].first;
        while(p){
            printf("%d",p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
    return OK;
}

int FirstAdjVex(ALGraph G, int x){
    //return the 1st node adjacent to node x(0-vexnum-1)
    if(x<0 || x>=G.vexnum)  return -1;
    ArcNode *p = G.v[x].first;
    if(p)   return p->adjvex;
    else return -1;
}

int NextAdjVex(ALGraph G, int x, int y){
    //return <x,y>'s next z s.t (s,z)
    if(x<0||x>=G.vexnum)    return -1;
    if(y<0||y>=G.vexnum)    return -1;
    ArcNode *p = G.v[x].first;
    while(p && p->adjvex!=y) p=p->nextarc;
    if(p && p->nextarc) return p->adjvex;
    else return -1;
}

Status InitOLGraph(OLGraPtr *P){
    (*P)=(OLGraPtr)malloc(sizeof(OLGraph));
    if(!(*P)) exit(OVERFLOW);
    return OK;
}

Status CreateOLGraph(OLGraph *G){
    printf("Enter vexnum and arcnum: ");
    scanf("%d%d",&(G->vexnum),&(G->arcnum));
    getchar();
    int i;
    //initilaize
    for(i=0;i<G->vexnum;i++){
        G->xlist[i].data = 'A'+i;
        G->xlist[i].firstout = G->xlist[i].fisrtin = NULL;
    }
    for(i=0;i<G->arcnum;i++){
        char x,y;
        printf("Enter edge%d(x->y is x y): ",i);
        scanf("%c%c",&x,&y); getchar();
        if(x<'A'||x>'Z'||y<'A'||y>'Z'){
            printf("Over bound A-Z\n");
            exit(OVERFLOW);
        }
        //construct
        ArcBox * arcPtr = (ArcBox *)malloc(sizeof(ArcBox));
        if(!arcPtr) exit(OVERFLOW);
        arcPtr->headvex = y-'A';
        arcPtr->tailvex = x-'A';
        arcPtr->hlink = G->xlist[y-'A'].fisrtin;
        arcPtr->tlink = G->xlist[x-'A'].firstout;
        G->xlist[y-'A'].fisrtin = arcPtr;
        G->xlist[x-'A'].firstout = arcPtr;
    }//for

    return OK;
}

Status ShowOLGraph(OLGraph G){
    int i;
    printf("Every node and the dege goes from it:\n");
    for(i=0;i<G.vexnum;i++){
        printf("(%d)%c: ",i,G.xlist[i].data);
        ArcBox * p = G.xlist[i].firstout;
        while(p){
            printf("(%c,%c)",p->tailvex+'A',p->headvex+'A');
            p = p->tlink;
        }
        printf("\n");
    }
    return OK;
}

//AMLGraph
Status InitAMLGraph(AMLGraPtr *G){
    (*G)=(AMLGraPtr)malloc(sizeof(AMLGraph));
    if(!(*G))   exit(OVERFLOW);
    return OK;
}

Status CreateAMLGraph(AMLGraph *G){
    int vn,en;
    printf("Enter vexnum and edgenum(vn en): ");
    scanf("%d%d",&(vn),&(en));
    getchar();
    if(vn<0 || en<0 || en>=MAX_VERTEX_NUM){
        printf("en:>=0\nvn:0-%d",MAX_VERTEX_NUM);
        return ERROR;
    }
    G->edgenum = en;
    G->vexnum = vn;
    //initialize
    int i;
    for(i=0;i<MAX_VERTEX_NUM;i++){
        G->adjmulist[i].data = 'A'+i;
        G->adjmulist[i].firstedga = NULL;
    }
    //input the edge
    for(i=0;i<G->edgenum;i++){
        char head,tail;
        printf("Enter vex (A-B)(eg:AB): ");//tail-head
        scanf("%c%c",&tail,&head); getchar();
        if(tail<'A'||tail>'Z'||head<'A'||head>'Z'){
            printf("Out of range!You should enter again!\n");
            i--;
            continue;
        }
        EBox * enode = (EBox*)malloc(sizeof(EBox));
        int ih = head - 'A';
        int it = tail - 'A';
        enode->ivex = it;
        enode->jvex = ih;
        enode->ilink = G->adjmulist[it].firstedga;
        enode->jlink = G->adjmulist[ih].firstedga;
        enode->mark = unvisited;
        G->adjmulist[it].firstedga = enode;
        //G->adjmulist[ih].firstedga = enode;
    }
    return OK;
}

Status ShowAMLGraph(AMLGraph G){
    int i;
    for(i=0;i<G.vexnum;i++){
        printf("(%d)%c --> ",i,G.adjmulist[i].data);
        EBox *p=G.adjmulist[i].firstedga;
        while(p){
            printf("<%c,%c>  ",p->ivex+'A',p->jvex+'A');
            p = p->ilink;
        }
        printf("\n");
    }
    return OK;
}

Status ShowAMLGedge(AMLGraph G,int i,int *n){ //i:the index of the node
    if(i<0 || i>G.vexnum){
        printf("Out of range!\n");
        return ERROR;
    }
    int j,num=0;
    for(j=0;j<G.vexnum;j++){
        EBox *p = G.adjmulist[j].firstedga;
        while(p){
            if((p->ivex==i)||(p->jvex==i)){
                num++;
            }
            p = p->ilink;
        }
    }
    *n = num;
    return OK;
}















