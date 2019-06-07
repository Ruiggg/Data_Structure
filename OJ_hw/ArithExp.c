#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3

typedef char TElemType;
typedef int Status;


typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild,*rchild; //left and right sons
} BiTNode,*BiTree;

Status PrintElement(TElemType e){
    printf("%c",e);
    return OK;
}
Status InOrderTraverse_OJ(BiTree T,Status(*Visit)(TElemType e),int tag){
    if(T){
        if(tag) printf("(");
        int thistag = ( (((T->data=='*')||(T->data=='\\'))&&(T->lchild)&&((T->lchild->data=='+')||(T->lchild->data=='-'))) )?1:0;
        if(InOrderTraverse_OJ(T->lchild,Visit,thistag)){
            if(Visit(T->data)){ //don't forget this step
                if( (T->data=='-'&&T->rchild&&T->rchild->data=='-')||(((T->data=='*')||(T->data=='\\'))&&(T->rchild)&&((T->rchild->data=='+')||(T->rchild->data=='-'))) ){
                    thistag = 1;
                }else thistag = 0;
                if(InOrderTraverse_OJ(T->rchild,Visit,thistag)){
                    if(tag) printf(")");
                    return OK;
                }
            }
        }
        return ERROR;
    }
    return OK;
}
#define QUEUESIZE 30
BiTree queue[QUEUESIZE];
int head=0,tail=0;
Status CreateBiTree_OJ_LevelTra_ch(BiTree *T){
    for(int m=0;m<QUEUESIZE;m++) queue[m]=NULL;
    char e,c;
    if(scanf("%c",&e)==1 && e!='n'){
        BiTree p = (BiTree)malloc(sizeof(BiTNode));
        if(!p) exit(OVERFLOW);
        p->data = e; p->lchild = NULL; p->rchild = NULL;
        queue[tail++] = p;
        (*T) = p;
        c = getchar();
        if(c=='\n') {return OK;}
    }else{
        while((c=getchar())!=',');
        (*T) = NULL;
        return OK;
    }
    while(tail!=head){
        BiTree q = queue[head++];
        //left son
        if(scanf("%c",&e)==1 && e!='n'){
            BiTree p1 = (BiTree)malloc(sizeof(BiTNode));
            if(!p1) exit(OVERFLOW);
            p1->data = e; p1->lchild = NULL; p1->rchild = NULL;
            queue[tail++] = p1;
            q->lchild = p1;
            c = getchar();
            if(c=='\n') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->lchild = NULL;
        }
        //right son
        if(scanf("%c",&e)==1 && e!='n'){
            BiTree p2 = (BiTree)malloc(sizeof(BiTNode));
            if(!p2) exit(OVERFLOW);
            p2->data = e; p2->lchild = NULL; p2->rchild = NULL;
            queue[tail++] = p2;
            q->rchild = p2;
            c = getchar();
            if(c=='\n') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->rchild = NULL;
        }
    }
    return OK;
}

int main(){
    testOJ();
}

void testOJ(){
    //OJ_PreTra();
    BiTree T;
    CreateBiTree_OJ_LevelTra_ch(&T);
    InOrderTraverse_OJ(T,PrintElement,0);
}




