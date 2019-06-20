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
        if(c=='\n') {return OK;}
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
            if(c=='\n') {return OK;}
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
            if(c=='\n') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->rchild = NULL;
        }
    }
    return OK;
}

int IsBST(BiTree T){
    if(!T) return 1;
    else if(T->lchild && T->rchild){
        if(T->lchild->data < T->data && T->data < T->rchild->data){
            int s1 = IsBST(T->lchild);
            int s2 = IsBST(T->rchild);
            if(s1&&s2) return 1;
            else return 0;
        }else return 0;
    }else if(T->lchild && !T->rchild){
        if(T->lchild->data < T->data){
            int s1 = IsBST(T->lchild);
            return s1;
        }else return 0;
    }else if(T->rchild && !T->lchild){
        if(T->rchild->data > T->data){
            int s1 = IsBST(T->rchild);
            return s1;
        }else return 0;
    }else
        return 1;
}


int main(){
    BiTree p;
    CreateBiTree_OJ_LevelTra(&p);
    printf("%d\n",IsBST(p));
}
