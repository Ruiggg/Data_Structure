#include <stdio.h>
#include <stdlib.h>
#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3

typedef int TElemType;
typedef int Status;

typedef enum PointerTag {Link,Thread} PointerTag;
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild,*rchild; //left and right sons
} BiTNode,*BiTree;

#define QUEUESIZE 30
BiTree queue[QUEUESIZE];
int head=0,tail=0;
Status CreateBiTree_OJ_LevelTra(BiTree *T){
    int e,c;
    if(scanf("%d",&e)==1){
        BiTree p = (BiTree)malloc(sizeof(BiTNode));
        if(!p) exit(OVERFLOW);
        p->data = e; p->lchild = NULL; p->rchild = NULL;
        queue[tail++] = p;
        (*T) = p;
        c = getchar();
        if(c==';') {return OK;}
    }else{
        while((c=getchar())!=',');
        (*T) = NULL;
        return OK;
    }
    while(tail!=head){
        BiTree q = queue[head++];
        //left son
        if(scanf("%d",&e)==1){
            BiTree p1 = (BiTree)malloc(sizeof(BiTNode));
            if(!p1) exit(OVERFLOW);
            p1->data = e; p1->lchild = NULL; p1->rchild = NULL;
            queue[tail++] = p1;
            q->lchild = p1;
            c = getchar();
            if(c==';') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->lchild = NULL;
        }
        //right son
        if(scanf("%d",&e)==1){
            BiTree p2 = (BiTree)malloc(sizeof(BiTNode));
            if(!p2) exit(OVERFLOW);
            p2->data = e; p2->lchild = NULL; p2->rchild = NULL;
            queue[tail++] = p2;
            q->rchild = p2;
            c = getchar();
            if(c==';') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->rchild = NULL;
        }
    }
    return OK;
}
int values[20];
int top=0;
Status SearchMiddleValues(BiTree T,int low,int high){
    if(T){
        SearchMiddleValues(T->lchild,low,high);
        if(T->data > low && T->data < high) values[top++]=T->data;
        SearchMiddleValues(T->rchild,low,high);
    }
    return OK;
}


int main(){
    BiTree p;
    CreateBiTree_OJ_LevelTra(&p);
    int low,high;
    scanf("%d",&low); getchar(); scanf("%d",&high);
    for(int i=0;i<20;i++) values[i]=0;
    SearchMiddleValues(p,low,high);
    for(int i=0;i<top;i++){
        printf("%d",values[i]);
        if(i<top-1) putchar(',');
    }
    return 0;
}













