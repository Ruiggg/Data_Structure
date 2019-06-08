#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "BiTree.h"


#define QUEUESIZE 30
//BiThrTree queue[QUEUESIZE];
//int head=0,tail=0;
Status CreateBiTree_OJ_LevelTra(BiTree *T){
    BiTree queue[QUEUESIZE];
    int head = 0, tail = 0;
    for(int h=0;h<QUEUESIZE;h++) queue[h] = NULL;

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

Status CreateBiTree_OJ_LevelTra_more(BiThrTree *T){
    BiThrTree queue[QUEUESIZE];
    int head = 0, tail = 0;
    for(int h=0;h<QUEUESIZE;h++) queue[h] = NULL;
    int e,c;
    if(scanf("%d",&e)==1){
        BiThrTree p = (BiThrTree)malloc(sizeof(BiThrNode));
        if(!p) exit(OVERFLOW);
        p->data = e; p->lchild = NULL; p->rchild = NULL; p->LTag=p->RTag=Link;
        queue[tail++] = p;
        (*T) = p;
        c = getchar();
        if(c!=',') {return OK;}
    }else{
        while((c=getchar())!=',');
        (*T) = NULL;
        return OK;
    }
    while(tail!=head){
        BiTree q = queue[head++];
        //left son
        if(scanf("%d",&e)==1){
            BiThrTree p1 = (BiThrTree)malloc(sizeof(BiThrNode));
            if(!p1) exit(OVERFLOW);
            p1->data = e; p1->lchild = NULL; p1->rchild = NULL; p1->LTag=p1->RTag=Link;
            queue[tail++] = p1;
            q->lchild = p1;
            c = getchar();
            if(c!=',') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->lchild = NULL;
        }
        //right son
        if(scanf("%d",&e)==1){
            BiThrTree p2 = (BiThrTree)malloc(sizeof(BiThrNode));
            if(!p2) exit(OVERFLOW);
            p2->data = e; p2->lchild = NULL; p2->rchild = NULL; p2->LTag=p2->RTag=Link;
            queue[tail++] = p2;
            q->rchild = p2;
            c = getchar();
            if(c!=',') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->rchild = NULL;
        }
    }
    return OK;
}


Status CreateBiTree_OJ_LevelTra_ch(BiTree *T){
    BiTree queue[QUEUESIZE];
    int head = 0, tail = 0;
    for(int h=0;h<QUEUESIZE;h++) queue[h] = NULL;


    int e,c;
    if(scanf("%c",&e)==1 && e!='n'){
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
        if(scanf("%c",&e)==1 && e!='n'){
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
        if(scanf("%c",&e)==1 && e!='n'){
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

Status InOrderTraverse_Thr2(BiThrTree T,Status(*Visit)(TElemType e)){
    if(T){
        if(InOrderTraverse_Thr2(T->lchild,Visit))
            if(Visit(T->data)) //don't forget this step
                if(InOrderTraverse_Thr2(T->rchild,Visit))
                    return OK;
        return ERROR;
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
    return OK;
}

Status OJ_PreTra(){
    BiTree p;
    CreateBiTree_OJ_LevelTra(&p);
    PreOrderTraverse_NR(p);
    //PreOrderTraverse(p,print);
    return OK;
}

Status InOrderTraverse_OJ(BiTree T,Status(*Visit)(TElemType e),int tag){
    if(T){
        if(tag) putchar('(');
        int thistag = ( (((T->data=='*')||(T->data=='\\'))&&(T->lchild)&&((T->lchild->data=='+')||(T->lchild->data=='-'))) )?1:0;
        if(InOrderTraverse_OJ(T->lchild,Visit,thistag)){
            if(Visit(T->data)){ //don't forget this step
                thistag = ( (T->data=='-'&&T->rchild&&T->rchild->data=='-')||(((T->data=='*')||(T->data=='\\'))&&(T->rchild)&&((T->rchild->data=='+')||(T->rchild->data=='-'))) )?1:0;
                if(InOrderTraverse_OJ(T->rchild,Visit,thistag)){
                    if(tag) putchar(')');
                    return OK;
                }
            }
        }
        return ERROR;
    }
    return OK;
}

BiThrTree findValueOf(int v,BiThrTree mom){
    if(!mom) return NULL;
    if(mom->data==v) return mom;
    else if(mom->LTag == Link){
        BiThrTree p = findValueOf(v,mom->lchild);
        if(p) return p;
    }else if(mom->RTag == Link){
        BiThrTree p = findValueOf(v,mom->rchild);
        if(p) return p;
    }
    return NULL;
}

Status AddtoNode(BiThrTree mom,BiThrTree son,BiThrTree p){
    if(p->LTag==Thread){
        BiThrTree tem = p->lchild;
        p->lchild = son;
        p->LTag = Link;
        BiThrTree node = son;
        while(node->LTag==Link) node = node->lchild;
        if(tem->RTag == Thread) tem->rchild = node;
        node->lchild = tem;
        son->RTag = Thread;
        son->rchild = p;
    }else{
        BiThrTree pleft = p->lchild;
        BiThrTree node = pleft;
        while(node->LTag==Link) node = node->lchild;
        BiThrTree tem = node;//1st of p's left tree
        BiThrTree prior = node->lchild;
        node = son;
        while(node->LTag==Link) node = node->lchild;
        node->lchild = prior;
        if(prior->RTag==Thread) prior->rchild = node;
        son->rchild = tem;
        tem->lchild = son;
        son->RTag = Link;
        son->rchild = p->lchild;
        p->lchild = son;
    }
    return OK;
}

Status ShowNodes(BiThrTree p){
    printf("%d,",p->LTag);
    printf("%d,",p->lchild->data);
    printf("%d,",p->RTag);
    printf("%d",p->rchild->data);
    if(p->rchild->data != 0) putchar(';');
    return OK;
}

Status ShowV(BiThrTree p){
    printf("%d,%d; ",p->lchild->data,p->rchild->data);
    return OK;
}

Status InOrderTraverse_Thr_OJ(BiThrTree T,Status(*Visit)(BiThrTree P)){
    //T: the head, not the root(=T->lchild)
    BiThrTree p;
    p = T->lchild;
    while(p!=T){
        while(p->LTag==Link) p=p->lchild;  //the "while" stops when p has no left child(LTag==Link means lchild is null)
        if(!Visit(p)) return ERROR;      //so it's time to visit it
        while(p->RTag==Thread && p->rchild!=T){ //and traverse the InOrder-Chain if any
            p=p->rchild;
            if(!Visit(p)) return ERROR;
        }//while ends when the node's right son is not null
        //and it means the prior node in the InOrder-chain has been visited;e.g. Every node in its left subtree has been visited
        //so:
        p=p->rchild;    //not p=p->l
    }

    return OK;
}

Status OJ_addThrInOder(){
    BiThrTree mom,son;
    CreateBiTree_OJ_LevelTra_more(&mom);
    CreateBiTree_OJ_LevelTra_more(&son);
    int node; scanf("%d",&node);

    BiThrTree Thrtmom,Thrtson;
    InOrderThreading(&Thrtmom,mom);
    InOrderThreading(&Thrtson,son);
    //InOrderTraverse_Thr(Thrtmom,print);
    //printf("\n");
    //InOrderTraverse_Thr(Thrtson,print);
    //puts("");
    BiThrTree p = findValueOf(node,mom);
    if(!p) return ERROR;
    AddtoNode(mom,son,p);
    InOrderTraverse_Thr_OJ(Thrtmom,ShowNodes);

    return OK;
}

















