#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "GeneralList.h"

GList_l InitGlist_l(ElemTag t){
    GList_l p = (GList_l)malloc(sizeof(GLNode_l));
    if(!GList_l) exit(OVERFLOW);
    p->tag=t; p->tp=NULL;
    if(ElemTag == ATOM)  p->atom=0;
    else  p->hp=p->tp=NULL;
    return p;
}

int GList_l_depth(GList_l l){
    if(!l) printf("l==NULL:undefined(empty list is not NULL)!!\n");
    if(l->tag==ATOM) return 0;
    if(l->hp==NULL) return 1;
    //the recursion
    GList_l pp;
    int max=0,dep;
    for(pp=l->hp;pp;pp=pp->tp){
        dep = GList_l_depth(pp);
        if(dep>max) max=dep;
    }
    return max+1;
}

Status CopyGlist_l(GList_l T,GList_l L){
    //T should init outside
    if(!L) printf("l==NULL:undefined(empty list is not NULL)!!\n");
    else {
        T=InitGlist_l(LIST);
        T->tag = L->tag;
        T->tp = L->tp;
        if(L->tag==ATOM) T->atom = L->atom;
        else if(L->hp==NULL);
        else {
            CopyGlist_l(T->hp,L->hp);
            CopyGlist_l(T->tp,L->tp);
        }
    }
    return OK;
}



















