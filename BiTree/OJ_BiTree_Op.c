#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "BiTree.h"


#define QUEUESIZE 30
BiTree queue[QUEUESIZE];
int head=0,tail=0;
Status CreateBiTree_OJ_LevelTra(BiTree *T){
    int e,c;
    if(scanf("%d",&e)==1){
        BiTree p = (BiTree)malloc(sizeof(BiTNode));
        if(!p) exit(OVERFLOW);
        p->data = e; p->lchild = NULL; p->rchild = NULL;
        queue[tail++] = p;
        (*T) = p;
        c = getchar();
        if(c=='\n') {return OK;}
    }else{
        while((c=getchar())!=',');
        (*T) = NULL;
        return OK;
    }
    while(tail!=head){
        BiTree q = queue[head++];
        //left son
        if(scanf("%d",&e)==1){
            BiTree p1 = (BiTree)malloc(sizeof(BiTNode));
            if(!p1) exit(OVERFLOW);
            p1->data = e; p1->lchild = NULL; p1->rchild = NULL;
            queue[tail++] = p1;
            q->lchild = p1;
            c = getchar();
            if(c=='\n') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->lchild = NULL;
        }
        //right son
        if(scanf("%d",&e)==1){
            BiTree p2 = (BiTree)malloc(sizeof(BiTNode));
            if(!p2) exit(OVERFLOW);
            p2->data = e; p2->lchild = NULL; p2->rchild = NULL;
            queue[tail++] = p2;
            q->rchild = p2;
            c = getchar();
            if(c=='\n') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->rchild = NULL;
        }
    }
    return OK;
}


Status PreOrderTraverse_NR(BiTree T){
    if(!T) return ERROR;
    int set[30],index=0;
    SqStack S;
    BiTree p;
    InitStack(&S); p=T;
    //printf("%d",p->data);
    set[index++] = p->data;
    if(p->lchild || p->rchild) Push(&S,p);
    p = p->lchild;
    while(p || !StackEmpty(S)){
        while(p){
            //printf("%d",p->data);
            set[index++] = p->data;
            if(p->lchild || p->rchild) {Push(&S,p);}
            p = p->lchild;
        }
        //end
        if(!StackEmpty(S)){
            if(Pop(&S,&p)!=OK) {return ERROR;}
            p = p->rchild;
        }
    }
    for(int i=0;i<index;i++){
        printf("%d",set[i]);
        if(i<index-1) putchar(',');
    }
    return OK;
}

Status print(TElemType e){
    printf("%d,",e);
}

Status OJ_PreTra(){
    BiTree p;
    CreateBiTree_OJ_LevelTra(&p);
    PreOrderTraverse_NR(p);
    //PreOrderTraverse(p,print);
    return OK;
}























