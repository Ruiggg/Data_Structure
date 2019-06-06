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

//about stack
typedef BiTree SElemType;
typedef struct Stack {
    SElemType * base;
    SElemType * top;
    int stacksize;
}SqStack;
Status InitStack(SqStack * S);
Status Push(SqStack *S,SElemType e);
Status Pop(SqStack *S,SElemType *e);
int StackEmpty(SqStack S);


#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

Status InitStack(SqStack * S){
    //create a empty stack
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S->base)
        exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *S,SElemType e){
    if(S->top - S->base >= S->stacksize) {
        S->base = (SElemType *)realloc(S->base,(S->stacksize + STACKINCREMENT)*sizeof(SElemType));
        if(!S->base)exit(OVERFLOW);

        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top++) = e;
    return OK;
}

Status Pop(SqStack *S,SElemType *e){
    if(S->top == S->base)return ERROR;
    *e = *(--S->top);
    return OK;
}

int StackEmpty(SqStack S){
    if(S.base==S.top)
        return 1;
    else
        return 0;
}






Status CreateBiTree_OJ_LevelTra(BiTree *T);
Status PreOrderTraverse_NR(BiTree T);
Status OJ_PreTra();


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


Status PreOrderTraverse_NR(BiTree T){
    if(!T) return ERROR;
    int set[30],index=0;
    SqStack S;
    BiTree p;
    InitStack(&S); p=T;
    //printf("%d",p->data);
    set[index++] = p->data;
    if(p->lchild || p->rchild) Push(&S,p);
    p = p->lchild;
    while(p || !StackEmpty(S)){
        while(p){
            //printf("%d",p->data);
            set[index++] = p->data;
            if(p->lchild || p->rchild) {Push(&S,p);}
            p = p->lchild;
        }
        //end
        if(!StackEmpty(S)){
            if(Pop(&S,&p)!=OK) {return ERROR;}
            p = p->rchild;
        }
    }
    for(int i=0;i<index;i++){
        printf("%d",set[i]);
        if(i<index-1) putchar(',');
    }
    return OK;
}

Status print(TElemType e){
    printf("%d,",e);
}

Status ChangeLR(BiTree T);

Status OJ_PreTra(){
    BiTree p;
    CreateBiTree_OJ_LevelTra(&p);
    ChangeLR(p);
    PreOrderTraverse_NR(p);
    //PreOrderTraverse(p,print);
    return OK;
}



Status ChangeLR(BiTree T){
    if(!T) return OK;
    BiTree tem = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tem;
    ChangeLR(T->lchild);
    ChangeLR(T->rchild);
}

int main(){
    testOJ();
}

void testOJ(){
    OJ_PreTra();
}




