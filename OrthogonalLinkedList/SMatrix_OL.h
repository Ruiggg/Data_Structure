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
Status InsertSMatrix_OL_II(OLink *m,OLink p,OLink *pre,OLink *hl,CrossList *M,CrossList *S);
Status AddSMatrix_OL(CrossList *M,CrossList *S);
Status LinkInColomn_SMatrix_OL(OLink *hl,OLink p,CrossList *M);
Status Check_TraverseCol(CrossList *M);
Status Check_TraverseRow(CrossList *M);
Status DeleteInColomn_SMatrix_OL(OLink *hl,OLink *m,CrossList *M);


//OJ
Status CreateSMatrix_OJ(CrossList *M,CrossList *N);
Status OJ_Print_SMatrix_OL(CrossList *M);


#endif // SMATRIX_OL_H_INCLUDED
