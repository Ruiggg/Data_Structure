#ifndef GENERALLIST_H_INCLUDED
#define GENERALLIST_H_INCLUDED
#define ATOM 0
#define LIST 1

typedef int Atomtype;   //int can be changed

//using head and tail storation format
//empty list pointer == NULL
typedef struct GLNode_th {
    ElemTag tag;
    union {
        Atomtype atom;
        struct {struct GLNode_th *hp,*tp;} ptr; //ptr.hp points to head, ptr.tp points to tail
    };
} GLNode_th,*GList_th;

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
