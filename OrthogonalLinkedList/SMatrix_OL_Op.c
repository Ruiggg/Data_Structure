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

Status AddSMatrix_OL(CrossList *M,CrossList *S){
//M = S+M
    if(M->mu!=S->mu || M->nu!=S->nu) return ERROR;

    OLink hl[M->nu];
    for(int i=0;i<M->nu;i++) hl[i]=M->chead[i];

    int row,col;
    for(row=0;row<M->mu;row++){ //tackle every row
        OLink m = M->rhead[row];
        OLink s = S->rhead[row];
        OLink pre = NULL;
        for(;s;s=s->right){
            OLink p = CreateOLNode(s->i,s->j,s->e);
            if(!p) return ERROR;
            InsertSMatrix_OL_II(&m,p,&pre,hl,M,S);
        }//for
    }//for
    return OK;
}

Status InsertSMatrix_OL_II(OLink *m,OLink p,OLink *pre,OLink *hl,CrossList *M,CrossList *S){
    int row = p->i;
    int col = p->j;
    int flag = 0;

    while(flag==0){
        if(!(*m) || (*m)->j > p->j){
            flag = 1;
            if(!(*pre)) { p->right = M->rhead[row]; M->rhead[row] = p;} //if fisrt insert
            else { p->right = (*pre)->right; (*pre)->right = p;}
            (*pre) = p;
            LinkInColomn_SMatrix_OL(hl,p,M);
        }
        else if((*m)->j == p->j){
            if((*m)->e + p->e != 0){
                (*m)->e += p->e,hl[p->j]=(*m);
            }else{
                if(!(*pre)) M->rhead[row]=(*m)->right;
                else{
                    (*pre)->right = (*m)->right;
                }
                DeleteInColomn_SMatrix_OL(hl,m,M);
                (*m) = (*m)->right;
            }//else
            flag = 1;
        }
        else
            (*pre)=(*m),(*m) = (*m)->right;
    }

    return OK;
}

//hl is changed only in link and delete
//p is not in M (do not check)
//hl will be changed to the node inserted
Status LinkInColomn_SMatrix_OL(OLink *hl,OLink p,CrossList *M){
//p: to be linked node
//hl:(1)NULL (2)The 1st under p (3)One above p
    int col = p->j;
    if(!hl[col]){ //only possible reason: chead[col] == NULL
        hl[col]=p;
        (M->chead)[col] = p;
        p->down = NULL;
    }
    else if(hl[col]->i < p->i){ //if at the beginning it is null
        while(hl[col] && hl[col]->down && hl[col]->down->i < p->i) hl[col]=hl[col]->down;
        p->down = hl[col]->down;
        hl[col]->down = p;
        hl[col] = p;

    }
    else if(hl[col]->i > p->i){
        p->down = hl[col];
        (M->chead)[col] = p;
        hl[col] = p;//big change
    }
    else return ERROR;
    return OK;
}

//delete one node **m in M in colomn
//if m is not the 1st in the col
//  hl[col] becomes m's pre
//else
//  hl[col] becomes m's successor
//
//hl[col] cannot be NULL, for the existence of m
//
Status DeleteInColomn_SMatrix_OL(OLink *hl,OLink *m,CrossList *M){
    int row = (*m)->i, col = (*m)->j;
    if((*m)==M->chead[col]) {
        M->chead[col] = hl[col] = (*m)->down;
        return OK;
    }else{
        //find the pre
        while(hl[col]->down && hl[col]->down->i < row) hl[col]=hl[col]->down;
        hl[col]->down = (*m)->down;
    }
    return OK;
}

Status Check_TraverseCol(CrossList *M){
    int col;
    for(col=0;col<M->nu;col++){
        printf("col %d: ",col);
        OLink p = M->chead[col];
        for(;p;p=p->down) printf("(%3d,%3d|%3d) ",p->i,p->j,p->e);
        printf("\n");
    }
    return OK;
}

Status Check_TraverseRow(CrossList *M){
    int row;
    for(row=0;row<M->mu;row++){
        printf("row %d: ",row);
        OLink p = M->rhead[row];
        for(;p;p=p->right) printf("(%3d,%3d|%3d) ",p->i,p->j,p->e);
        printf("\n");
    }
    return OK;
}





