#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "GeneralList.h"
#include "MPNode.h"


Status InitGlist_l(GList_l *p){
//create an empty list
    *p = (GList_l)malloc(sizeof(GLNode_l));
    if(!*p) exit(OVERFLOW);
    (*p)->tag = LIST;
    (*p)->hp = (*p)->tp=NULL;
    return OK;
}

GList_l CreateGLNode_l(ElemTag t){
    GList_l p = (GList_l)malloc(sizeof(GLNode_l));
    if(!p) exit(OVERFLOW);
    p->tag = t;
    if(t==ATOM) p->atom = 0;
    else p->hp = NULL;
    p->tp = NULL;
    return p;
}

Status CreateTestGL_l(GList_l l){
    //l has been inited
    //L = ((a))
    if(!l) {printf("Forget to init l\n"); return ERROR;}
/*    GList_l first1 = CreateGLNode_l(LIST);
    first1->tp = NULL;
    GList_l first11 = CreateGLNode_l(ATOM);
    first11->atom = 'a';
    first11->tp = NULL;
    first1->hp = first11;
    l->hp = first1;
    return OK;
*/
    //L = (a,(b,c,c))
    GList_l f1 = CreateGLNode_l(ATOM); //a
    f1->atom = 'a';
    l->hp = f1;
    GList_l s1 = CreateGLNode_l(LIST); //(b c d)
    s1->tp = NULL;
    f1->tp = s1;
    GList_l f2 = CreateGLNode_l(ATOM); // b
    f2->atom = 'b';
    s1->hp = f2;
    GList_l s2 = CreateGLNode_l(ATOM); // c
    s2->atom = 'c';
    f2->tp = s2;
    GList_l t2 = CreateGLNode_l(ATOM); //d
    t2->atom = 'c';
    s2->tp = t2;
    t2->tp = NULL;
    return OK;
//*/
}

int GList_l_depth(GList_l l){
    if(!l) {printf("l==NULL:undefined(empty list is not NULL)!!\n"); return ERROR;}
    if(l->hp==NULL) return 1;
    //if(l->hp->tag==ATOM) return 1;
    if(l->tag==ATOM) return 0;//because the same
    //the recursion
    GList_l pp;
    int max=0,dep;
    for(pp=l->hp;pp;pp=pp->tp){
        dep = GList_l_depth(pp);
        if(dep>max) max=dep;
    }
    return max+1;
}

Status CopyGlist_l(GList_l *T,GList_l L){
    //*T = L;
    if(L){
        if(L->tag==ATOM){
            *T = CreateGLNode_l(ATOM);
            (*T)->atom = L->atom;
        }else{
            *T = CreateGLNode_l(LIST);
            CopyGlist_l(&((*T)->hp),L->hp);
        }
        CopyGlist_l(&((*T)->tp),L->tp);
    }else
        *T = NULL;
    return OK;
}

Status PrintGL_l(GList_l l){
    if(l){
        if(l->tag==ATOM){
            printf("%2c",l->atom);
        }else{
            printf(" (");
            GList_l pp;
            for(pp = l->hp; pp ; pp = pp->tp){
                PrintGL_l(pp);
            }
            printf(" )");
        }
    }
    return OK;
}

Status InsertFirst_GL_l(GList_l l,ElemType e){
//insert an atom node to the fisrt position
    if(l){
        if(l->tag == LIST){
            GList_l p = CreateGLNode_l(ATOM);
            p->atom = e;
            p->tp = l->hp;
            l->hp = p;
        }else{
            printf("Can't insert to an Atom.\n");
        }
    }
    return OK;
}

Status DeleteFisrt_GL_l(GList_l l,ElemType *e){
//delete the first atom node or the first atom node of the fisrt element(recursively)
    if(l){
        if(l->tag == LIST){
            if(l->hp){
                if(l->hp->tag == ATOM){
                    GList_l tem = l->hp;
                    *e = tem->atom;
                    l->hp = l->hp->tp;
                    free(tem);
                }else{
                    DeleteFisrt_GL_l(l->hp,e);
                }
            }
            //if () nothing occurs
        }else{
            *e = l->atom;
            printf("Can't delete to an Atom.\n");
        }
    }
    return OK;
}

Status DeleteFisrtElem_GL_l(GList_l l){
//delete first element no matter what it is
    if(l){
        if(l->tag == LIST){
            if(l->hp){// l is not empty
                //GList tem = l->hp;
                l->hp = l->hp->tp;
                //Destroy(tem);
            }
        }else{
            printf("Can't delete to an Atom.\n");
        }
    }
    return OK;
}

Status DeleteNode_GL_l(GList_l l,ElemType e){
    if(l){
        if(l->hp){
            GList_l pp,pre;
            pre = l;
            for(pp = l->hp ; pp ; pp=pp->tp){
                if(pp->tag==ATOM && pp->atom==e){
                    if(pre==l){
                        l->hp = pp->tp;
                        free(pp);
                    }else{
                        pre->tp = pp->tp;
                        free(pp);
                    }
                }else if(pp->tag==LIST){
                    DeleteNode_GL_l(pp,e);
                    pre = pp;
                }else
                    pre = pp;
            }//for
        }//if
    }//if
    return OK;
}











