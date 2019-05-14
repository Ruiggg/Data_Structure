#ifndef TSMATRIX_H_INCLUDED
#define TSMATRIX_H_INCLUDED

#include "Predefined_const.h"
#define MAXSIZE 12500
#define MAXRC 100

//typedef int ElemType;
typedef struct {
    int i,j;
    ElemType e;
}Triple;

typedef struct {
    Triple data[MAXSIZE+1];         //data[0] is used
    int mu,nu,tu;                   //m*n Matrix and the number of tu elements are not 0
                                    // m:row       n:colomn
}TSMatrix;

Status CreateTestTSMatrix(TSMatrix *m);
Status CreateTSMatrix(TSMatrix *m);
Status InsertToTSMatrix(TSMatrix* m,int row,int col,int ele);
Status PrintTSArray(TSMatrix* m); //use for debug
int NotZero(TSMatrix* M,int m,int n);
Status PrintSMatrix(TSMatrix * m);
Status TransposeTSMatrix(TSMatrix *T,TSMatrix *M);
Status FastTransposeTSMatrix(TSMatrix *T,TSMatrix *M);




typedef struct {
    Triple data[MAXSIZE+1];
    int rpos[MAXRC+1];              //the position(eg. index) in the data[] of the 1st non-zero element(if any) in each row
    int mu,nu,tu;
}RLSMatrix;


Status InsertToRLSMatrix(RLSMatrix* m,int row,int col,int ele);
Status RLSpos(RLSMatrix *M);
Status CreateRLSMatrix(RLSMatrix *m);
Status MultRLSMatrix(RLSMatrix *d,RLSMatrix *t,RLSMatrix *s);
int RNotZero(RLSMatrix *M,int m,int n);
Status PrintRLSMatrix(RLSMatrix *M);

#endif // TSMATRIX_H_INCLUDED
