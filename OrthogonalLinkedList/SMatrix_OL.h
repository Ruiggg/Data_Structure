#ifndef SMATRIX_OL_H_INCLUDED
#define SMATRIX_OL_H_INCLUDED


typedef struct OLNode {
    int i,j;//i:row; j:col
    CLMElemType e;
    struct OLNode *right,*down;
}OLNode,*OLink;

typedef struct {
    OLink *rhead,*chead; //store the pointer pointing to the first elem in each row and column
    int mu,nu,tu;
}CrossList;



Status CreateSMatrix_OL(CrossList *M);
Status InsertSMatrix_OL(CrossList *M,int row,int col,CLMElemType value);
OLink CreateOLNode(int row,int col,CLMElemType value);
Status PrintSMatrix_OL(CrossList *M);



#endif // SMATRIX_OL_H_INCLUDED
