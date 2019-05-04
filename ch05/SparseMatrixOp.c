//the operation can only be used for Triple array structure
//M.data[i] 's i is start from 1

//CreateSMatrix(TSMatrix * M){};
//DestroySMatrix(TSMatrix * M){};
#include "SparseMatrix.h"
#include "Predefined_const.h"
#include <stdio.h>
int NotZero(TSMatrix M,int m,int n){
    int s;
    for(s=1;s<=M.tu;s++){
        if(m==M.data[s].i && n==M.data[s].j)
            return s;
    }
    return 0;
}

Status PrintSMatrix(TSMatrix M){
    int i,j,p;
    for(i=0;i<M.mu;i++){
        for(j=0;j<M.nu;j++){
            if((p=NotZero(M,i,j))!=0)
                printf("%5d",M.data[p].e);      //the argument %5d can be changed by the type of ElemTYpe
            else
                printf("%5d",0);
        }//for j
        printf("\n");
    }//for u
    return OK;
}


Status CopySMatrix(TSMatrix M,TSMatrix * T){
    return OK;
}

Status AddSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q){
    return OK;
}

Status SubSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q){
    return OK;
}

Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q){
    //the function is based on RLSMatrix
    if(M.nu != N.mu)
        return ERROR;

    Q->mu = M.mu;
    Q->nu = N.nu;
    Q->rpos[0]=1;
    int ctemp[N.nu];        //play a role of adder for one row of Q
    int d,row,p,q;
    int pos=1;                //the position of element of Q in Q.data

    //for every row of M
    for(row=0;row<M.mu;row++){
        // set it 0 each time!!!
        for(d=0;d<N.nu;d++)
            ctemp[d]=0;
        //if we are in the last row, so the rpos[row+1] is undefined, and it may be very large, resulting in overflow
        int tp = (row<M.mu-1)?M.rpos[row+1]:M.tu+1; //the M.rpos[row+1]should always be M.tu+1;

        for(p=M.rpos[row];p < tp;p++){
            int col = M.data[p].j;      //col also represents n's row

            int t = (col < N.mu - 1)?N.rpos[col+1]:N.tu+1;

            for(q=N.rpos[col] ; q < t; q++){
                ctemp[N.data[q].j] += M.data[p].e * N.data[q].e;
            }
        }
        //assign ctemp[] to Q
        int t;
        for(t=0;t<N.nu;t++){
            if(ctemp[t]!=0){
                Q->data[pos].e = ctemp[t];
                Q->data[pos].i = row;
                Q->data[pos].j = t;
                pos++;
            }
        }
        Q->rpos[row+1] = pos;
    }
    Q->tu = pos-1;
    return OK;
}

Status TransposeSMatrix(TSMatrix M,TSMatrix *T){
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;
    if(T->tu){
        int col,p;
        int s=1;        //s is the index of the T.data, and T.data[s] is to be assingned
        for(col = 0; col < M.nu ;col ++){
            for(p = 1; p <= M.tu ;p++){
                if(col == M.data[p].j){
                    T->data[s].i = col;
                    T->data[s].j = M.data[p].i;
                    T->data[s].e = M.data[p].e;
                    s++;            //do not forget it!!!
                }
            }
        }
    }
    return OK;
}

Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T){
    //num[col] is the number of elements in M's col column
    //cpot[col] is the position of the 1st non-zero element which has not been put into T.data --
    //--in T.data, so cpot[col] is changing after the 1st assignment
    int num[M.nu];
    int cpot[M.nu];

    int col;
    for(col=0;col<M.nu;col++)
        num[col]=cpot[col]=0;
    int p;
    for(p=1;p<=M.tu;p++)        //scan every non-zero elements in M
        num[M.data[p].j]++;     //using the adder to compute the number of elements in every colomn

    cpot[0] = 1;
    for(p=1;p<M.nu;p++)
        cpot[p]=num[p-1]+cpot[p-1];

    for(p=1;p<=M.tu;p++){
        col = M.data[p].j;
        int q = cpot[col];
        T->data[q].i = col;
        T->data[q].j = M.data[p].i;
        T->data[q].e = M.data[p].e;
        cpot[col] ++;
    }
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;
    return OK;
}

int RNotZero(RLSMatrix M,int m,int n){
    int s;
    for(s=1;s<=M.tu;s++){
        if(m==M.data[s].i && n==M.data[s].j)
            return s;
    }
    return 0;

}

Status PrintRLSMatrix(RLSMatrix M){
    int i,j,p;
    for(i=0;i<M.mu;i++){
        for(j=0;j<M.nu;j++){
            if((p=RNotZero(M,i,j))!=0)
                printf("%5d",M.data[p].e);      //the argument %5d can be changed by the type of ElemTYpe
            else
                printf("%5d",0);
        }//for j
        printf("\n");
    }//for u
    printf("\n");
    return OK;
}

Status Rpos(RLSMatrix *M){
    int num[M->mu];  //to store the number of elements in every row
    int p;
    for(p=0;p<M->mu;p++)
        num[p] = 0;
    for(p=1;p<=M->tu;p++)
        num[M->data[p].i]++;

    M->rpos[0] = 1;
    for(p=1;p<M->mu;p++)
        M->rpos[p] = M->rpos[p-1] + num[p-1];
    return OK;
}





