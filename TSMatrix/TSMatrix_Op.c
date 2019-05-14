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

Status PrintTSArray(TSMatrix* m){
    int k;
    for(k=0;k<m->tu;k++){
        printf("%d %d : %d \n",m->data[k].i,m->data[k].j,m->data[k].e);
    }
    return OK;
}

Status PrintSMatrix(TSMatrix *M){
     int i,j,p;
     for(i=0;i<M->mu;i++){
        for(j=0;j<M->nu;j++){
            if((p=NotZero(M,i,j))!=-1)
                printf("%5d",M->data[p].e);      //the argument %5d can be changed by the type of ElemTYpe
            else
                printf("%5d",0);
        }//for j
        printf("\n");
    }//for u
    return OK;
}

int NotZero(TSMatrix *M,int m,int n){
    int s;
    for(s=0;s<M->tu;s++){
        if(m==M->data[s].i && n==M->data[s].j)
            return s;
    }
    return -1;
}

Status TransposeTSMatrix(TSMatrix *T,TSMatrix *M){
    T->mu = M->nu;
    T->nu = M->mu;
    T->tu = M->tu;
    int s = 0;  //the pos in T to be added
    int col,p;
    for(col=0;col<M->nu;col++){
        for(p=0;p<M->tu;p++){
            if(col == M->data[p].j){
                T->data[s].i = M->data[p].j;
                T->data[s].j = M->data[p].i;
                T->data[s].e = M->data[p].e;
                s++;
            }
        }
    }
    return OK;
}


Status Sing(void){

//你都如何回忆我

//带着笑或是很沉默

//这些年来

//有没有人能让你不寂寞

//后来

//我总算学会了 如何去爱

//可惜你 早已远去

//消失在人海

    return OK;
}

Status FastTransposeTSMatrix(TSMatrix *T,TSMatrix *M){
    T->mu = M->nu;
    T->nu = M->mu;
    T->tu = M->tu;
    int num[M->nu]; //the number of non-zero element for each column of M
    int cpot[M->nu]; //the position in T (to be added) of each column of M
    //initialize
    int p;
    for(p=0;p<M->nu;p++) num[p]=cpot[p]=0;
    for(p=0;p<M->tu;p++) num[M->data[p].j]++;
    for(p=1;p<M->nu;p++) cpot[p]=cpot[p-1]+num[p-1];
    for(p=0;p<M->tu;p++){
        T->data[cpot[M->data[p].j]].i = M->data[p].j;
        T->data[cpot[M->data[p].j]].j = M->data[p].i; //really hard to read NP-hard!! 2333
        T->data[cpot[M->data[p].j]].e = M->data[p].e;
        cpot[M->data[p].j]++;
    }
    return OK;
}


Status InsertToRLSMatrix(RLSMatrix* m,int row,int col,int ele){
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
            //printf("Error: the place has been taken! Nothing done.\n");
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

Status RLSpos(RLSMatrix *M){
    int num[M->mu];  //to store the number of elements in every row
    int p;
    for(p=0;p<M->mu;p++)
        num[p] = 0;
    for(p=0;p<M->tu;p++)
        num[M->data[p].i]++;
    M->rpos[0] = 0;
    for(p=1;p<M->mu;p++)
        M->rpos[p] = M->rpos[p-1] + num[p-1];
    return OK;
}

Status CreateRLSMatrix(RLSMatrix *m){
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
            if(InsertToRLSMatrix(m,row,col,ele)!=OK) return ERROR; //tu has inc in this function
        }
    }while(row>=0 && col>=0 && m->tu < rownum*colnum);
    RLSpos(m);
    //int z;
    //for(z=0;z<m->mu;z++)printf("%3d",m->rpos[z]);
    //printf("\n");
    return OK;
}

Status MultRLSMatrix(RLSMatrix *d,RLSMatrix *t,RLSMatrix *s){
// d = t * s
// running error may occur if one matrix's size is 0
    if(t->nu != s->mu){/*printf("Size error.\n");*/ return ERROR;}
    d->mu = t->mu;
    d->nu = s->nu;
    d->tu = 0;//initial
    ElemType ctemp[s->nu]; //acc for a row
    int row;
    for(row=0;row<t->mu;row++){ //row is the index of row
        //initialize the ctemp
        int col=0;
        for(;col<s->nu;col++) ctemp[col]=0; //col is the index of col

        int index;
        int end_t = (row==(t->mu-1))?t->tu:t->rpos[row+1]; //for rpos[mu] is not defined

        for(index=t->rpos[row]; index < end_t ;index++){
            //find the corresponding element when multiply
            int s_row = t->data[index].j;
            int end_s = (s_row==(s->mu-1))?s->tu:s->rpos[s_row+1];

            int x;//the index of ele in t->data
            for(x=s->rpos[s_row];x<end_s;x++){
                int indexInCtemp = s->data[x].j;
                ctemp[indexInCtemp] += (t->data[index].e * s->data[x].e);
            }
        }//for
        //create nodes in d
        int l;
        for(l=0;l<s->nu;l++){
            if(ctemp[l]!=0){
                d->data[d->tu].i = row;
                d->data[d->tu].j = l;
                d->data[d->tu].e = ctemp[l];
                d->tu++;
            }
        }
    }//for
    return OK;
}


int RNotZero(RLSMatrix *M,int m,int n){
    int s;
    for(s=0;s<M->tu;s++){
        if(m==M->data[s].i && n==M->data[s].j)
            return s;
    }
    return -1;
}

Status PrintRLSMatrix(RLSMatrix *M){
     int i,j,p;
     for(i=0;i<M->mu;i++){
        for(j=0;j<M->nu;j++){
            if((p=RNotZero(M,i,j))!=-1)
                printf("%5d",M->data[p].e);      //the argument %5d can be changed by the type of ElemTYpe
            else
                printf("%5d",0);
        }//for j
        printf("\n");
    }//for u
    return OK;
}
















