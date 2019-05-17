#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "SMatrix_OL.h"
//3;2;[[2,0];[4,0];[0,0]]+[[0,0];[7,0];[1,0]]
Status CreateSMatrix_OJ(CrossList *M,CrossList *N){
    scanf("%d",&(M->mu)); getchar(); N->mu = M->mu; M->tu = 0;
    scanf("%d",&(M->nu)); getchar(); N->nu = M->nu; N->tu = 0;
    int m,n;

    M->rhead = (OLink*)malloc((M->mu)*sizeof(OLink));
    M->chead = (OLink*)malloc((M->nu)*sizeof(OLink));
    for(int s=0;s<M->mu;s++) (M->rhead)[s] = NULL;
    for(int s=0;s<M->nu;s++) (M->chead)[s] = NULL;

    N->rhead = (OLink*)malloc((N->mu)*sizeof(OLink));
    N->chead = (OLink*)malloc((N->nu)*sizeof(OLink));
    for(int s=0;s<N->mu;s++) (N->rhead)[s] = NULL;
    for(int s=0;s<N->nu;s++) (N->chead)[s] = NULL;

    getchar();//[
    for(m=0;m<M->mu;m++){
        getchar();//[
        for(n=0;n<M->nu;n++){
            int value; scanf("%d",&value);
            getchar();//, ]
            if(value) InsertSMatrix_OL(M,m,n,value),M->tu++;
        }
        getchar(); //; ]
    }
    getchar(); //+
    getchar(); //[
    for(m=0;m<M->mu;m++){
        getchar();//[
        for(n=0;n<M->nu;n++){
            int value; scanf("%d",&value);
            getchar();//, ]
            if(value) InsertSMatrix_OL(N,m,n,value),N->tu++;
        }
        getchar(); //; ]
    }
    return OK;
}


Status OJ_Print_SMatrix_OL(CrossList *M){
    printf("%c",'[');
    int m,n;
    for(m=0;m<M->mu;m++){
        printf("%c",'[');
        OLink p = M->rhead[m];
        for(n=0;n<M->nu;n++){
            if(p && p->j==n){
                if(n==0) printf("%d",p->e);
                else printf(",%d",p->e);
                p = p->right;
            }else{
                if(n==0) printf("%d",0);
                else printf(",%d",0);
            }
        }
        printf("%c",']');
        if(m<M->mu-1) printf(";");
    }
    printf("%c",']');
    return OK;
}

