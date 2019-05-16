#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "SMatrix_OL.h"

Status CreateSMatrix_OL(CrossList *M){
    printf("Input rownum,colnum,totalnum: ");
    scanf("%d%d%d",&(M->mu),&(M->nu),&(M->tu));//not check rightness

    M->rhead = (OLink*)malloc((M->mu)*sizeof(OLink));
    M->chead = (OLink*)malloc((M->nu)*sizeof(OLink));
    for(int s=0;s<M->mu;s++) (M->rhead)[s] = NULL;
    for(int s=0;s<M->nu;s++) (M->chead)[s] = NULL;

    int num;
    for(num=0;num<M->tu;num++){
        printf("Input row,col,element: ");
        int row,col,value;
        scanf("%d%d%d",&row,&col,&value);
        if(!InsertSMatrix_OL(M,row,col,value)) return ERROR;
    }
    return OK;
}

Status InsertSMatrix_OL(CrossList *M,int row,int col,CLMElemType value){
    if(row<0||row>=M->mu||col<0||col>=M->nu) return ERROR;
    OLNode* node = CreateOLNode(row,col,value);
    if(!node) return ERROR;
    OLink rowp = M->rhead[row];
    OLink colp = M->chead[col];
    //link to the row
    if(rowp==NULL||rowp->j > col){
        node->right = rowp;
        M->rhead[row] = node;
    }else if(rowp->j < col){
        while(rowp->right && rowp->right->j <= col) rowp=rowp->right;
        if(col==rowp->j) return ERROR;
        node->right = rowp->right;
        rowp->right = node;
    }else return ERROR;
    //link to the col
    if(colp==NULL || colp->i > row){
        node->down = colp;
        M->chead[col] = node;
    }else if(colp->i < row){
        while(colp->down && colp->down->i <= row) colp = colp->down;
        if(row==colp->i) return ERROR;
        node->down = colp->down;
        colp->down = node;
    }else return ERROR;
    return OK;
}

OLink CreateOLNode(int row,int col,CLMElemType value){
    OLink p = (OLink)malloc(sizeof(OLNode));
    if(p){
        p->i = row;
        p->j = col;
        p->e = value;
        p->down = p->right = NULL;
    }
    return p;
}

Status PrintSMatrix_OL(CrossList *M){
    //only use rows
    int m,n;
    OLink p;
    for(m=0;m<M->mu;m++){
        p = M->rhead[m];
        for(n=0;n<M->nu;n++){
            if(p && p->j==n){
                printf("%5d",p->e);
                p = p->right;
            }else
                printf("%5d",0);
        }
        printf("\n");
    }
    printf("\n");
    return OK;
}









