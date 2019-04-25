#ifndef OLMATRIX_H_INCLUDED
#define OLMATRIX_H_INCLUDED
#include "Predefined_const.h"
#include "stdlib.h"
typedef struct OLNode {
    int i,j;
    ElemType e;
    struct OLNode * right,* down;
} OLNode, *OLink;

typedef struct {
    OLink * rhead,* chead;  //rhead and chead should be initilized to be an array of OLink
    int mu,nu,tu;
}CrossList;

Status CreateSMatrix_OL(CrossList *M);
Status PrintSMatrix_OL(CrossList M);
Status AddOLMatrix(CrossList *A,CrossList B);
Status MyAddOLMatrix(CrossList *A,CrossList B);

#endif // OLMATRIX_H_INCLUDED
