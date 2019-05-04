#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "GeneralList.h"


Status InitGlist_th(GList_th * p,ElemTag t){
    //e is a
    (*p) = (GList_th)malloc(sizeof(GLNode_th));
    if(!(*p)) exit(OVERFLOW);
    (*p)->tag = t;
    if(t==LIST){
        ((*p)->ptr).hp = NULL;
        ((*p)->ptr).tp = NULL;
    }else{
        ((*p)->atom)=0;
    }
    return OK;
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

Status CopyGlist_th(GList_th *T,GList_th L){
    if(!L) {*T=NULL; return OK;}
    InitGlist_th(T,L->tag);
    if(L->tag==ATOM){(*T)->atom=L->atom; return OK;}
    GList_th head,tail;
    CopyGlist_th(&head,(L)->ptr.hp);
    CopyGlist_th(&tail,(L)->ptr.tp);
    (*T)->ptr.hp = head;
    (*T)->ptr.tp = tail;
    return OK;
}

GList_th CreateGLNode_th(ElemTag t){
    GList_th p = (GList_th)malloc(sizeof(GLNode_th));
    if(!p) exit(OVERFLOW);
    p->tag = t;
    return p;
}

Status CreateTestGL_th(GList_th l){
    //l has been inited
    //C = (a,(b,c,d))
    l->tag = LIST;
    //create the head node "a"
    GList_th h1 = CreateGLNode_th(ATOM);
    h1->atom = 'a';
    //link h1
    l->ptr.hp = h1;
    //create the tail ((b,c,d))
    GList_th t1 = CreateGLNode_th(LIST);
    //link tail list
    l->ptr.tp = t1;
    //creadte the head of t1  ht1:(b,c,d)
    GList_th ht1 = CreateGLNode_th(LIST);
    //link ht1 to t1
    t1->ptr.hp = ht1;
    t1->ptr.tp = NULL;
    //create the head of ht1 hht1:b
    GList_th hht1 = CreateGLNode_th(ATOM);
    hht1->atom = 'b';
    //link hht1 to ht1
    ht1->ptr.hp = hht1;
    //create the tail of ht1 ---tht1:(c,d)
    GList_th tht1 = CreateGLNode_th(LIST);
    //link tht1 to ht1
    ht1->ptr.tp = tht1;
    //create the head of tht1  --- htht1:c
    GList_th htht1 = CreateGLNode_th(ATOM);
    htht1->atom = 'c';
    //link
    tht1->ptr.hp = htht1;
    //create the tail of tht1  ttht1:(d)
    GList_th ttht1 = CreateGLNode_th(LIST);
    //link
    tht1->ptr.tp = ttht1;
    GList_th httht1 = CreateGLNode_th(ATOM);
    httht1->atom = 'd';
    //link
    ttht1->ptr.hp = httht1;
    ttht1->ptr.tp = NULL;
    return OK;
}

Status PrintGL_th(GList_th l){
    if(l){
        if(l->tag == ATOM){
            printf("%2c",l->atom);
            return OK;
        }
        printf(" (");
        while(l){
            PrintGL_th(l->ptr.hp);
            l = l->ptr.tp;
        }
        printf(" )");
    }else{
        printf("()");
    }
    return OK;
}

Status DestroyGList_th(GList_th l){
    if(!l) return OK;
    if(l->tag==ATOM){free(l); return OK;}
    //list node
    if(l->tag!=LIST){printf("Construction error!"); return ERROR;}
    DestroyGList_th(l->ptr.hp);
    DestroyGList_th(l->ptr.tp);
    free(l);
    return OK;
}

int GList_th_length(GList_th l){
    if(!l) return 0;
    if(l->tag==ATOM) return 1;
    int length_head = GList_th_length(l->ptr.hp);
    int length_tail = GList_th_length(l->ptr.tp);
    return length_head+length_tail;
}

int GList_th_empty(GList_th l){
    return (l==NULL);
}

GList_th getHead_GL_th(GList_th l){
    if(GList_th_empty(l)){
        printf("l is empty!");
        return NULL;
    }else{
        return l->ptr.hp;
    }
}

Status InsertFirst_GL_th(GList_th *l, ElemType e){
    GList_th tail = *l;
    GList_th newGl = CreateGLNode_th(LIST);
    //link
    newGl->ptr.tp = tail;
    GList_th head = CreateGLNode_th(ATOM);
    head->atom = e;
    //link
    newGl->ptr.hp = head;
    *l = newGl;
    return OK;
}

Status DeleteFisrt_GL_th(GList_th *l, ElemType* e){
    if(!(*l)){printf("Error:l shouldb't be empty!\n"); return ERROR;}
    if((*l)->tag == ATOM){
        printf("ERROR:l should be a list node");
        *e = (*l)->atom;
        //free(l);
        return ERROR;
    }
    if((*l)->ptr.hp==NULL){
        printf("Warning: the 1st element is an empty Glist\nNothing to return.\n");
        return OK;
    }
    if((*l)->ptr.hp->tag==LIST){
        DeleteFisrt_GL_th(&((*l)->ptr.hp),e);
        return OK;
    }
    if((*l)->ptr.hp->tag==ATOM){
        *e = (*l)->ptr.hp->atom;
        free((*l)->ptr.hp);
        (*l) = ((*l)->ptr.tp);
        return OK;
    }
    return OK;
}

Status DeleteNode_GL_th(GList_th *l,ElemType x){
    //delete nodes whose value is x
    if(*l){
        if((*l)->tag==LIST){
            if((*l)->ptr.hp!=NULL){
                if((*l)->ptr.hp->tag==ATOM && (*l)->ptr.hp->atom==x){
                    int tem;
                    DeleteFisrt_GL_th(l,&tem);
                }else{
                    DeleteNode_GL_th(&( (*l)->ptr.hp ),x);
                    DeleteNode_GL_th(&( (*l)->ptr.tp ),x);
                }
            }
        }
    }
    return OK;
}

