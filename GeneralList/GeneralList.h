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


//using chains storation(sub-list analysis storation)
//needs a node representing the list itself(like a header), whose hp points to the first element in the Glist
//empty list pointer != NULL, but its hp anf tp == NULL
typedef struct GLNode_l {
    ElemTag tag;
    union {
        Atomtype atom;
        struct GLNode_l * hp;   //pointing to the first element of what this List-node represent.
    };
    struct GLNode_l *tp;    //the next element in the same layer, that is, the same list

} GLNode_l,*GList_l;

Status InitGlist_l(GList_l *p);
Status CreateTestGL_l(GList_l l);
int GList_l_depth(GList_l l);
Status CopyGlist_l(GList_l *T,GList_l L);
Status PrintGL_l(GList_l l);
Status InsertFirst_GL_l(GList_l l,ElemType e);
Status DeleteFisrt_GL_l(GList_l l,ElemType *e);
Status DeleteFisrtElem_GL_l(GList_l l);
Status DeleteNode_GL_l(GList_l l,ElemType e);
Status DeleteNode_GL_l(GList_l l,ElemType e);

#endif // GENERALLIST_H_INCLUDED
