#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "GeneralList.h"

GList_th InitGlist_th(ElemTag t){
    GList_th p = (GList_th)malloc(sizeof(GLNode_th));
    if(!p)  exit(OVERFLOW);
    p->tag = t;
    if(t==LIST){
        (p->ptr).hp = NULL;
        (p->ptr).tp = NULL;
    }else{
        (p->atom)=0;
    }
    return p;
}

int GList_th_depth(GList_th l){
    if(!l) return 1;
    if(l->tag==ATOM) return 0;
    //if not empty list or elemental node
    int head_depth,tail_depth;
    head_depth = GList_th_depth(l->ptr.hp); //depth-1
    tail_depth = GList_th_depth(l->ptr.tp); //depth, for you add a () to the tail
    if(head_depth+1>=tail_depth)
        return (head_depth+1);
    else
        return tail_depth;
}

int GListDepth(GList_th L){
    //tail-head general list
    if(L->tag==ATOM)    return 0;   //have to be first
    if(!L)  return 1;
    //if(L->tag==ATOM)    return 0;
    int max,dep;
    GList_th pp;
    for(pp=L,max=0;pp;pp=pp->ptr.tp){
        dep = GListDepth(pp->ptr.hp);   //GetHead[GetTail(k)[L]] gets the k-1 th element/list in Glist
        if(dep>max) max = dep;
    }
    return max+1;
}

Status CopyGlist_th(GList_th T,GList_th L){
    //We assume that T is initialized and not points to any other in the outside
    if(!L)  T=NULL; //if L == NULL
    else{
        T->tag = L->tag; //do not forget copy tag of L to T!!!
        if(L->tag==ATOM){
            free(T);
            T=InitGlist_th(ATOM);
            T->atom = L->atom;
        }else{
            CopyGlist_th(&(T->ptr.hp),L->ptr.hp);
            CopyGlist_th(&(T->ptr.tp),L->ptr.tp);
        }
    }
    return OK;
}


















