#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "BiTree.h"



Status CreateBiTree(BiTree *T){
    //preorder
    //"#"means empty tree
    //construct T
    TElemType c;
    scanf("%c",&c);
    if(c=='#')
        (*T)=NULL;
    else {
        if(!((*T)=(BiTree)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
        (*T)->data = c;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
    return OK;
}


Status PrintElement(TElemType e){
    printf("%c",e);
    return OK;
}

Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e)){
    if(T){
        if(Visit(T->data))
            if(PreOrderTraverse(T->lchild,Visit))
                if(PreOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }else return OK;
}


Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e)){
    if(T){
        if(InOrderTraverse(T->lchild,Visit))
            if(Visit(T->data)) //don't forget this step
                if(InOrderTraverse(T->rchild,Visit))
                    return OK;
        return ERROR;
    }
    return OK;
}

Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e)){
    if(T){
        if(PostOrderTraverse(T->lchild,Visit))
            if(PostOrderTraverse(T->rchild,Visit)) //don't forget this step
                if(Visit(T->data))
                    return OK;
        return ERROR;
    }
    return OK;
}

Status InOrderTraverse_NR1(BiTree T,Status(*Visit)(TElemType e)){
    //non-recursion algorithm
    SqStack S;
    BiTree p;
    InitStack(&S);  Push(&S,T);
    while(!StackEmpty(S)){
        while((GetTop(S,&p))&& p)
            Push(&S,p->lchild);
        Pop(&S,&p); //pop null
        if(!StackEmpty(S)){
            Pop(&S,&p); if(!Visit(p->data)) return ERROR;
            Push(&S,(p->rchild));
        }//if
    }//while
    return OK;
}

Status InOrderTraverse_NR2(BiTree T,Status(*Visit)(TElemType e)){
    SqStack S;
    BiTree p;
    InitStack(&S); p=T;
    while(p || !StackEmpty(S)){
        if(p) {Push(&S,p); p=p->lchild;}
        else {
            Pop(&S,&p);
            if(!Visit(p->data)) return ERROR;
            p=p->rchild;
        }
    }
    return OK;
}

Status PostOrderTraverse_NR(BiTree T,Status(*Visit)(TElemType e)){
    SqStack S;
    BiTree p = T,pre=NULL;
    InitStack(&S);
    while(p || !StackEmpty(S)){
        if(p) {Push(&S,p); p=p->lchild;}//the shun xu is important
        else {  //p has no left child
            GetTop(S,&p);
            if(!(p->rchild)){   //p is a leaf
                Visit(p->data);
                pre = p;
                Pop(&S,&p);
                p = NULL;
                //if(!StackEmpty(S)) Pop(&S,&p);
            }else if(p->lchild==pre){
                p=p->rchild;
            }else if(p->rchild==pre){
                Visit(p->data);
                pre = p;
                Pop(&S,&p);
                p = NULL;
            }
        }
    }
    return OK;
}

Status InOrderThreading(BiThrTree *Thrt,BiThrTree T){
    //InOrderTraverse BiThrTree T
    //Threaden T
    if(!(*Thrt=(BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
    //Thrt is the header
    //Thrt->lchild = T;
    BiThrTree pre;
    (*Thrt)->data = 0;
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;
    (*Thrt)->rchild = *Thrt;  //At the beginning, thrt's success is itself
    if(!T)  (*Thrt)->lchild  = *Thrt;   //you have to take the situation into consideration
    else {
        (*Thrt)->lchild = T;   pre = *Thrt;
        InThreading(T,&pre);
        pre->rchild = *Thrt; pre->RTag = Thread;
        (*Thrt)->rchild = pre;
    }
    return OK;
}

void InThreading(BiThrTree p, BiThrTree *pre){
    if(p){
        p->LTag = p->RTag = Link;
        InThreading(p->lchild,pre);
        if(!p->lchild){
            p->lchild = *pre;
            p->LTag = Thread;
        }
        if(!(*pre)->rchild){
            (*pre)->rchild = p;
            (*pre)->RTag = Thread;
        }
        *pre = p;
        InThreading(p->rchild,pre);
    }
}

Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(TElemType e)){
    //T: the head, not the root(=T->lchild)
    BiThrTree p;
    p = T->lchild;
    while(p!=T){
        while(p->LTag==Link) p=p->lchild;  //the "while" stops when p has no left child(LTag==Link means lchild is null)
        if(!Visit(p->data)) return ERROR;      //so it's time to visit it
        while(p->RTag==Thread && p->rchild!=T){ //and traverse the InOrder-Chain if any
            p=p->rchild;
            if(!Visit(p->data)) return ERROR;
        }//while ends when the node's right son is not null
        //and it means the prior node in the InOrder-chain has been visited;e.g. Every node in its left subtree has been visited
        //so:
        p=p->rchild;    //not p=p->l
    }

    return OK;
}

Status CreateThrBiTree(BiThrTree *T){
    //preorder
    //"#"means empty tree
    //construct T
    TElemType c;
    scanf("%c",&c);
    if(c=='#')
        (*T)=NULL;
    else {
        if(!((*T)=(BiThrTree)malloc(sizeof(BiThrNode)))) exit(OVERFLOW);
        (*T)->data = c;
        CreateThrBiTree(&((*T)->lchild));
        CreateThrBiTree(&((*T)->rchild));
    }
    return OK;
}

Status FindInOrderParent_Thr(BiThrTree T, BiThrNode ** parent, BiThrNode *p){
    if(p==T)  {*parent=NULL; return ERROR;}
    BiThrNode *ptr = p;
    while(ptr->RTag == Link) ptr=ptr->rchild;
    ptr = ptr->rchild;
    if(ptr->lchild == p){*parent=ptr; return OK;}
    ptr = p;
    while(ptr->LTag == Link) ptr=ptr->lchild;
    ptr = ptr->lchild;
    if(ptr->rchild == p){*parent=ptr; return OK;}
    printf("Error occurs while finding parents\n");
    exit(OVERFLOW);

    return OK;
}

Status FindPostOrderFirst_Thr(BiThrTree T, BiThrNode ** p){
    //T the pointer to the root node, not the head
    //no matter which kind of threaten it is
    BiThrNode* pre,*ptr;
    ptr = T; pre = NULL;
    while(ptr->LTag == Link) ptr=ptr->lchild;
    if(ptr->RTag == Thread) { *p = ptr; return OK;}
    else    FindPostOrderFirst_Thr(ptr->rchild,p);
    return OK;
}

//non-recursion version
Status FindPostOrderFirst_Thr_NR(BiThrTree T, BiThrNode ** p){
    //T the pointer to the root node, not the head
    //no matter which kind of threaten it is
    BiThrNode* ptr;
    ptr = T;
    while(ptr->LTag==Link || ptr->RTag==Link){
        while(ptr->LTag == Link) ptr=ptr->lchild;
        if(ptr->RTag == Link) ptr = ptr->rchild;
    }
    *p = ptr;
    return OK;
}


Status FindPOScr_IOThr(BiThrTree T, BiThrNode * p,BiThrNode **successor){
    //find post-order successor of p in an full InOrder_Thr_Tree
    BiThrNode * parent;
    FindInOrderParent_Thr(T,&parent,p);
    if(!parent){ return ERROR;}
    else if(parent->rchild == p) {*successor=parent; return OK;}
    else if(parent->RTag==Thread) {*successor=parent; return OK;}
    else{
        FindPostOrderFirst_Thr_NR(parent->rchild,successor);
    }
    return OK;
}

Status CheckFPOSIOT(BiThrTree T){
    BiThrNode *succ=NULL;
    BiThrNode *p;
    FindPostOrderFirst_Thr_NR(T,&p);
    while(p->LTag == Link) p=p->lchild;
    while(FindPOScr_IOThr(T,p,&succ)==OK){
        printf("Present: %-5c Next: %-5c\n",p->data,succ->data);
        p = succ;
    }
    return OK;
}







