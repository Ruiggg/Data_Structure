#ifndef GENERALLIST_H_INCLUDED
#define GENERALLIST_H_INCLUDED
#define ATOM 0
#define LIST 1
#include "MPNode.h"//!!!

typedef int Atomtype;   //int can be changed

//using head and tail storation format
//empty list pointer == NULL
typedef struct GLNode_th {
    ElemTag tag;// int
    union {
        Atomtype atom;
        struct {struct GLNode_th *hp,*tp;} ptr; //ptr.hp points to head, ptr.tp points to tail
    };
} GLNode_th,*GList_th;

Status InitGlist_th(GList_th * p,ElemTag t);
int GList_th_depth(GList_th l);
int GListDepth(GList_th L);
Status CopyGlist_th(GList_th *T,GList_th L);
GList_th CreateGLNode_th(ElemTag t);
Status CreateTestGL_th(GList_th l);
Status PrintGL_th(GList_th l);
Status DestroyGList_th(GList_th l);
int GList_th_length(GList_th l);
int GList_th_empty(GList_th l);
GList_th getHead_GL_th(GList_th l);
Status InsertFirst_GL_th(GList_th *l, ElemType e);
Status DeleteFisrt_GL_th(GList_th *l, ElemType* e);
Status DeleteNode_GL_th(GList_th* l,ElemType x);


//using chains storation
//needs a node representing the list itself(like a header), whose hp points to the first element in the Glist
//empty list pointer != NULL, but its hp anf tp == NULL
typedef struct GLNode_l {
    ElemTag tag;
    union {
        Atomtype atom;
        struct GLNode_l * hp;
    };
    struct GLNode_l *tp;

} GLNode_l,*GList_l;

#endif // GENERALLIST_H_INCLUDED
