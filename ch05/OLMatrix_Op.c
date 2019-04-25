#include "OLMatrix.h"
#include <stdio.h>


Status CreateSMatrix_OL(CrossList *M){
    //if(M) free(M);  //ensure M is empty
    printf("Please input the row and colomu:");
    int row,col;
    scanf("%d%d",&row,&col);

    M->mu = row;
    M->nu = col;
    M->tu = 0;

    M->rhead = (OLink *)malloc(row*sizeof(OLink));
    if(!M->rhead) exit(OVERFLOW);

    M->chead = (OLink *)malloc(col*sizeof(OLink));
    if(!M->chead) exit(OVERFLOW);

    int index;
    for(index = 0;index < M->mu;index++)
        M->rhead[index]=NULL;
    for(index=0;index<M->nu;index++)
        M->chead[index]=NULL;

    while(1){
        printf("Enter h,l,e,(i=-1 to stop): ");
        int h,l,elem;
        scanf("%d%d%d",&h,&l,&elem);   //i>=0,j>=0
        if(h<0 || h>=row || l<0 || l>=col)
            break;

        OLink olk = (OLink)malloc(sizeof(OLNode));
        if(!olk)  exit(OVERFLOW);
        olk->i = h;
        olk->j = l;
        olk->e = elem;
        olk->down = NULL;
        olk->right = NULL;
        M->tu ++;

        if((M->rhead)[h] == NULL || ((M->rhead)[h]->j) > (l)){
            olk->right = M->rhead[h];
            M->rhead[h] = olk;
        }else if((M->rhead[h]->j) < l){
            OLink tem = M->rhead[h];
            while(tem->right != NULL && tem->right->j < l)
                tem = tem->right;
            olk->right = tem->right;
            tem->right = olk;
        }else{
            printf("The position has been taken in the row!\nInput again!\n");
            free(olk);
            continue;
            M->tu--;
        }

        if(M->chead[l]==NULL || (M->chead[l]->i) > h){
            olk->down = M->chead[l];
            M->chead[l] = olk;
        }else if((M->chead[l]->i) < h){
            OLink pr=M->chead[l];
            while(pr->down != NULL && pr->down->i < h)
                pr = pr->down;
            //pr->down = olk; An error, for warning!!!
            olk->down = pr->down;
            pr->down = olk;
        }else{
            printf("The position has been taken in the column!\nInput again!\n");
            free(olk);
            continue;
            M->tu--;
        }
    }
    return OK;
}


Status PrintSMatrix_OL(CrossList M){
    int m,n;
    for(m=0;m<M.mu;m++){
        OLink opr = M.rhead[m];
        for(n=0;n<M.nu;n++){
            if(opr!=NULL && opr->j == n){
                printf("%5d",opr->e);
                opr = opr->right;
            }
            else{
                printf("%5d",0);
            }
        }
        printf("\n");
    }
    printf("\n");
    return OK;
}


Status MyAddOLMatrix(CrossList *A,CrossList B){
    //A = A+B, so B is not changed
    if(A->mu != B.mu){
        printf("A.mu!=B.mu\n");
        return ERROR;
    }
    if(A->nu!=B.nu){
        printf("A.nu!=B.nu\n");
        return ERROR;
    }
    OLink pre;
    OLink hl[A->nu];        //at the begining of each circle,hl are the immediate upper of elemwnts in this row
    int k;
    for(k=0;k<A->nu;k++){   //initialize hl[]
        hl[k] = A->chead[k];
    }
    for(k=0;k<A->mu;k++){
        pre = NULL;
        OLink pa = A->rhead[k];
        OLink pb = B.rhead[k];
        while(pb != NULL){  //for element pb in B's row k
            //scan every ele in A's row A till pa==null or pa.j==pb.j(if any) or pa.j>pb.j(if no pa==pb)
            if(pa==NULL){//only pre in the left of pb
                //create a node
                OLink p = (OLink)malloc(sizeof(OLNode));
                if(!p)  exit(OVERFLOW);
                p->i = pb->i;
                p->j = pb->j;
                p->e = pb->e;
                p->down = p->right = NULL;
                //determine whether it is the start of a row
                if(pre==NULL){
                    A->rhead[k] = p;
                    pre=p;
                }
                else{
                    pre->right = p;
                    pre=p;
                }
                if(A->chead[p->j]==NULL){
                    A->chead[p->j] = p;
                    hl[p->j] = p;
                }
                else if(p->i < hl[p->j]->i){ //p is upper
                    if(hl[p->j]==A->chead[p->j])
                        A->chead[p->j] = p;
                    p->down = hl[p->j];
                    hl[p->j]=p;
                }
                else if(p->i > hl[p->j]->i){ //p is lower
                    p->down = hl[p->j]->down;
                    hl[p->j]->down = p;
                    hl[p->j] = p;
                }
            }
            else if(pa!=NULL && pa->j > pb->j){
                //create a node
                OLink p = (OLink)malloc(sizeof(OLNode));
                if(!p)  exit(OVERFLOW);
                p->i = pb->i;
                p->j = pb->j;
                p->e = pb->e;
                p->down = p->right = NULL;
                if(pre==NULL){
                    p->right = pa;
                    pre = p;
                    A->rhead[k] = pre;
                }else{
                    pre->right = p;
                    p->right = pa;
                    pre = p;
                }
                if(A->chead[p->j]==NULL){
                    A->chead[p->j] = p;
                    hl[p->j] = p;
                }
                else if(hl[p->j]->i > p->i){
                    p->down = hl[p->j];
                    hl[p->j] = p;
                    if(hl[p->j]==A->chead[p->j])
                        A->chead[p->j] = p;
                }else if(hl[p->j]->i < p->i){
                    p->down = hl[p->j]->down;
                    hl[p->j]->down = p;
                    hl[p->j] = p;
                }
            }
            else if(pa->j == pb->j){
                if(pa->e+pb->e != 0)
                    pa->e += pb->e;
                else{
                    if(pre==NULL){
                        A->rhead[k] = pa->right;
                    }
                    else{
                        pre->right = pa->right;
                    }
                    if(hl[pa->j]==A->chead[pb->j]){
                        hl[pa->j]=pa->down;
                        A->chead[pb->j] = pa->down;
                        free(pa);
                    }
                    else{
                        hl[pa->j]->down = pa->down;
                        free(pa);
                    }
                }
            }
            else{
                pre = pa;
                pa = pa->right;
                //pre = pa;
            }
            pb=pb->right;
        }

        int l;
        for(l=0;l<A->nu;l++){
            if(hl[l]->down != NULL && hl[l]->down->i < k)
                hl[l]=hl[l]->down;
        }
    }
    return OK;
}

OLink CreateOLNode(int ii,int jj,int ee){
    OLink p = (OLink)malloc(sizeof(OLNode));
                if(!p)  exit(OVERFLOW);
                p->i = ii;
                p->j = jj;
                p->e = ee;
                p->down = p->right = NULL;
                return p;
}

//My own thinking is false
Status AddOLMatrix(CrossList *A,CrossList B){
    //initialize
     if(A->mu != B.mu){
        printf("A.mu!=B.mu\n");
        return ERROR;
    }
    if(A->nu!=B.nu){
        printf("A.nu!=B.nu\n");
        return ERROR;
    }
    OLink pre;
    OLink hl[A->nu];        //at the begining of each circle,hl are the immediate upper of elemwnts in this row
    int k;
    for(k=0;k<A->nu;k++){   //initialize hl[]
        hl[k] = A->chead[k];
    }
    //
    for(k=0;k<A->mu;k++){
        pre = NULL;
        OLink pa = A->rhead[k];
        OLink pb = B.rhead[k];
        while(pb!=NULL){
            OLink p = CreateOLNode(pb->i,pb->j,pb->e);
            if(!pa || pa->j > pb->j){
                if(!pre) {A->rhead[k] = p,p->right= A->rhead[k];pre=p;}//we should pre=p!!
                else {p->right=pre->right; pre->right=p;pre=p;}//dont't forget pre=p!!,for now pa is null,so pre is the last
                int col = pb->j;    //the index of column
                while(hl[col] && hl[col]->down && hl[col]->down->i < k)
                    hl[col]=hl[col]->down;
                if(!hl[col]) {p->down=A->chead[col];A->chead[col]=p;hl[col]=p;}
                else if(!hl[col]->down) { //hl[col] impossible to be lower except only one in the column
                    if(hl[col]->i < k) {p->down=hl[col]->down; hl[col]->down=p;}
                    else {p->down=hl[col]; A->chead[col]=p;hl[col]=p;}
                }else {p->down=hl[col]->down; hl[col]->down=p;}
            }else if(pa->j == pb->j){
                if(pa->e + pb->e != 0) pa->e += pb->e;
                else{
                    if(!pre) A->rhead[k]=pa->right;
                    else {pre->right=pa->right;}
                    //shanchu lie
                    int col = pb->j;    //the index of column
                    while(hl[col] && hl[col]->down && hl[col]->down->i < k)
                        hl[col]=hl[col]->down;
                    if(!hl[col]) {p->down=A->chead[col];A->chead[col]=p;hl[col]=p;}
                    else if(!hl[col]->down) { //hl[col] impossible to be lower except only one in the column
                        if(hl[col]->i < k) {p->down=hl[col]->down; hl[col]->down=p;}
                        else {p->down=hl[col]; A->chead[col]=p;hl[col]=p;}
                    }else {p->down=hl[col]->down; hl[col]->down=p;}
                }
            }else{
                pre=pa;
                pa = pa->right;
            }
            pb=pb->right;
        }//while
    }//for
    return OK;
}















