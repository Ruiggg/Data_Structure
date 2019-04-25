#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"
#include "Predefined_const.h"
#include <string.h>
#define MAXWIGHT 10000

Status Select(HuffmanTree HT,int up,int *s1,int *s2){
    if(up<2)    return ERROR;
    int m1,m2;
    m1 = 0;
    m2 = 0;
    int w1,w2;
    w1 = MAXWIGHT;
    w2 = MAXWIGHT;

    int i;
    //assuming w1<=w2
    for(i=1;i<=up;i++){
        if(HT[i].weight<w1 && HT[i].parent==0){
            w2=w1,m2=m1;
            m1=i,w1=HT[i].weight;
        }else if(HT[i].weight<w2 && HT[i].parent==0){
            m2=i,w2=HT[i].weight;
        }
    }
    *s1 = m1;
    *s2 = m2;
    return OK;
}

Status HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n){
    if(n<=1)    return ERROR;
    //w[] :the weight of every characters
    //n: the number of characters
    if(n<=1)    return ERROR;
    int m = 2*n-1;
    (*HT) = (HuffmanTree)malloc((m+1)*sizeof(HTNode));    //HT[0] is unused
    if(!(*HT)) exit(OVERFLOW);
    //initialize: each chars is a root node: index 1---n
    int i;
    for(i=1;i<=n;i++){
        (*HT)[i].weight = w[i-1];
        (*HT)[i].lchild = (*HT)[i].rchild = (*HT)[i].parent = 0;
    }
    //index n---2n-1,the new interior nodes
    for(;i<=m;i++){
        (*HT)[i].weight=0;
        (*HT)[i].lchild = (*HT)[i].rchild = (*HT)[i].parent = 0;
    }
    //building the HuffmanTree
    for(i=n+1;i<=m;i++){
        int s1,s2;
        Select(*HT,i-1,&s1,&s2);
        (*HT)[i].lchild=s1;  (*HT)[i].rchild=s2;
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }

//---------coding-------//
    //(*HT) = (HuffmanTree)malloc(sizeof(HuffmanCode)*(m+1));    //HT[0] is unused
    (*HC) = (HuffmanCode)malloc((n+1)*sizeof(char*));
    if(!HC) exit(OVERFLOW);
    //working array
    char *cd = (char*)malloc(n*sizeof(char));
    if(!cd) exit(OVERFLOW);
    cd[n-1]='\0';

    for(i=1;i<=n;i++){
        int j,k;
        for(j=i,k=n-1;j!=m;j=(*HT)[j].parent){  //for HT[m] is always the root node
            int tem = (*HT)[j].parent;
            if((*HT)[tem].lchild==j)    cd[--k]='0';
            else cd[--k]='1';
        }

        (*HC)[i] = (char*)malloc((n-k)*sizeof(char));
        strcpy((*HC)[i],cd+k);
    }
    free(cd);
    return OK;
}

Status PrintHuffmanCode(HuffmanCode HC,int n){
    int i;
    for(i=1;i<=n;i++){
        printf("%s\n",HC[i]);
    }
    return OK;
}

Status HuffmanCoding_UPD(HuffmanTree *HT,HuffmanCode *HC,int *w,int n){
    if(n<=1)    return ERROR;
    //w[] :the weight of every characters
    //n: the number of characters
    if(n<=1)    return ERROR;
    int m = 2*n-1;
    (*HT) = (HuffmanTree)malloc((m+1)*sizeof(HTNode));    //HT[0] is unused
    if(!(*HT)) exit(OVERFLOW);
    //initialize: each chars is a root node: index 1---n
    int i;
    for(i=1;i<=n;i++){
        (*HT)[i].weight = w[i-1];
        (*HT)[i].lchild = (*HT)[i].rchild = (*HT)[i].parent = 0;
    }
    //index n---2n-1,the new interior nodes
    for(;i<=m;i++){
        (*HT)[i].weight=0;
        (*HT)[i].lchild = (*HT)[i].rchild = (*HT)[i].parent = 0;
    }
    //building the HuffmanTree
    for(i=n+1;i<=m;i++){
        int s1,s2;
        Select(*HT,i-1,&s1,&s2);
        (*HT)[i].lchild=s1;  (*HT)[i].rchild=s2;
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }

//---------coding-------//
    //from root to leaves
    (*HC) = (HuffmanCode)malloc((n+1)*sizeof(char*));
    if(!HC) exit(OVERFLOW);
    //working array
    char *cd = (char*)malloc(n*sizeof(char));
    if(!cd) exit(OVERFLOW);
    //using wight to help traverse
    for(i=1;i<=m;i++) (*HT)[i].weight=0;
    int p=m; int cdlen=0;
    while(p){
        if((*HT)[p].weight==0){
            (*HT)[p].weight=1;  //there +1!!!
            if((*HT)[p].lchild!=0){
                p=(*HT)[p].lchild;
                cd[cdlen]='0';
                cdlen++;
            }else{  //lchild==0, for the preperty of HuffmanTree,p has to be a leaf
                (*HC)[p] = (char*)malloc((cdlen+1)*sizeof(char));
                cd[cdlen]='\0';
                strcpy((*HC)[p],cd);
            }
        }else if((*HT)[p].weight==1){
            (*HT)[p].weight=2;
            if((*HT)[p].rchild==0){
                p=(*HT)[p].parent;
                cdlen--;
            }else{  //should traverse the right subtree
                p=(*HT)[p].rchild;
                cd[cdlen]='1';
                cdlen++;
            }
        }else{
            //(*HT)[p].weight=0;
            p=(*HT)[p].parent;
            cdlen--;
        }
    }

    return OK;
}





