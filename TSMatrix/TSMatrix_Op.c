#include "Predefined_const.h"
#include "TSMatrix.h"
#include <stdio.h>
#include <stdlib.h>

Status CreateTestTSMatrix(TSMatrix *m){
    m->tu = 8;
    m->mu = 6;
    m->nu = 7;
    m->data[0].i = 0;
    m->data[0].j = 3;
    m->data[0].e = 22;
    m->data[1].i = 0;
    m->data[1].j = 6;
    m->data[1].e = 15;
    m->data[2].i = 1;
    m->data[2].j = 1;
    m->data[2].e = 11;
    m->data[3].i = 1;
    m->data[3].j = 5;
    m->data[3].e = 17;
    m->data[4].i = 2;
    m->data[4].j = 3;
    m->data[4].e = -6;
    m->data[5].i = 3;
    m->data[5].j = 5;
    m->data[5].e = 39;
    m->data[6].i = 4;
    m->data[6].j = 0;
    m->data[6].e = 91;
    m->data[7].i = 5;
    m->data[7].j = 2;
    m->data[7].e = 28;
    return OK;
}

Status CreateTSMatrix(TSMatrix *m){
    int rownum,colnum;//input
    do{
        printf("Enter rownum and colnum: ");
        scanf("%d%d",&rownum,&colnum);
        getchar();
    }while(rownum<=0 || colnum<=0);
    m->mu = rownum;
    m->nu = colnum;
    m->tu = 0;
    int row,col,ele;
    do{
        printf("Enter row, col and element(row col element)(any <0 to  stop): ");
        scanf("%d%d%d",&row,&col,&ele); getchar();
        if(row>=0 && col>=0){
            InsertToTSMatrix(m,row,col,ele); //tu has inc in this function
        }
    }while(row>=0 && col>=0 && m->tu < rownum*colnum);

    return OK;
}

Status InsertToTSMatrix(TSMatrix* m,int row,int col,int ele){
    if(row<0 || col<0) return ERROR;
    int k=0;
    if(m->tu > 0){
        while(m->data[k].i < row && k < m->tu){
            k++;
        }//until i >= row
        if(m->data[k].i == row){
            while(m->data[k].j < col && m->data[k].i==row && k<m->tu){ k++; }
        }//until i=row,j>=col
        if(m->data[k].i==row && m->data[k].j==col){
            printf("Error: the place has been taken! Nothing done.\n");
            return ERROR;
        }
        int q = m->tu;
        for(;q > k;q-- ) m->data[q] = m->data[q-1];
    }
    // if tu=0 , k=0, else k is the postion to be inserted
    m->data[k].i = row;
    m->data[k].j = col;
    m->data[k].e = ele;
    m->tu++;
    return OK;
}

Status PrintTSArray(TSMatrix m){
    int k;
    for(k=0;k<m.tu;k++){
        printf("%d %d : %d \n",m.data[k].i,m.data[k].j,m.data[k].e);
    }
    return OK;
}

Status PrintSMatrix(TSMatrix M){
     int i,j,p;
     for(i=0;i<M.mu;i++){
        for(j=0;j<M.nu;j++){
            if((p=NotZero(M,i,j))!=-1)
                printf("%5d",M.data[p].e);      //the argument %5d can be changed by the type of ElemTYpe
            else
                printf("%5d",0);
        }//for j
        printf("\n");
    }//for u
    return OK;
}

int NotZero(TSMatrix M,int m,int n){
    int s;
    for(s=0;s<M.tu;s++){
        if(m==M.data[s].i && n==M.data[s].j)
            return s;
    }
    return -1;
}









