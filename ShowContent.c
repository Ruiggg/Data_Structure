#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3
#define QUEUESIZE 30

typedef char TElemType;
typedef int Status;



//child-sibling hoard format
typedef struct CSNode {
    TElemType data;
    //struct CSNode * parent;
    struct CSNode * firstchild,*nextsibling;
}CSNode,*CSTree;


Status CreateBiTree_OJ_LevelTra_ch(CSTree *T){
    CSTree queue[QUEUESIZE];
    int head = 0, tail = 0;
    for(int h=0;h<QUEUESIZE;h++) queue[h] = NULL;


    char e,c;
    if(scanf("%c",&e)==1 && e!='n'){
        CSTree p = (CSTree)malloc(sizeof(CSNode));
        if(!p) exit(OVERFLOW);
        p->data = e; p->firstchild = NULL; p->nextsibling = NULL;
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
        CSTree q = queue[head++];
        //left son
        if(scanf("%c",&e)==1 && e!='n'){
            CSTree p1 = (CSTree)malloc(sizeof(CSNode));
            if(!p1) exit(OVERFLOW);
            p1->data = e; p1->firstchild = NULL; p1->nextsibling = NULL;
            queue[tail++] = p1;
            q->firstchild = p1;
            c = getchar();
            if(c=='\n') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->firstchild = NULL;
        }
        //right son
        if(scanf("%c",&e)==1 && e!='n'){
            CSTree p2 = (CSTree)malloc(sizeof(CSNode));
            if(!p2) exit(OVERFLOW);
            p2->data = e; p2->firstchild = NULL; p2->nextsibling = NULL;
            queue[tail++] = p2;
            q->nextsibling = p2;
            c = getchar();
            if(c=='\n') {return OK;}
        }else{
            while((c=getchar())!=',');
            q->nextsibling = NULL;
        }
    }
    return OK;
}



Status PrintContent(CSTree T,int i){
    if(T){
        int j = i;
        for(;i>0;i--) printf(" ");
        printf("%c",T->data);
        putchar('\n');
        PrintContent(T->firstchild,j+1);
        PrintContent(T->nextsibling,j);
    }
    return OK;
}


int main(void){
    CSTree T;
    CreateBiTree_OJ_LevelTra_ch(&T);
    PrintContent(T,0);
    return 0;
}
