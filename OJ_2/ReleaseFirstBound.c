#include <stdio.h>
#include <stdlib.h>



#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3

#define FootLoc(p) p+p->size-1
typedef int Status;

typedef struct WORD {
    struct WORD * llink;   //former
    int uplink;
    int tag;
    int size;       //next
    struct WORD * rlink;
}WORD,head,foot,*Space;


Status BuildList(WORD **pav){
    int size,startaddr;
    char tag;
    WORD * pre = NULL;
    WORD * p = NULL;
    while((tag=getchar())=='0'||tag=='1'){
        p = (WORD*)malloc(sizeof(WORD));
        if(!p) exit(OVERFLOW); p->tag = tag-'0';
        getchar(); scanf("%d",&(p->rlink)); getchar(); scanf("%d",&(p->size)); getchar();
        if(pre){
            pre->rlink = p;
            p->llink = pre;
        }else
            (*pav) = p;
        pre = p;
    }
    getchar();
    pre->rlink = (*pav);
    (*pav)->llink = pre;
    return OK;
}

WORD* ReadaRow(){
    tag = getchar();
    if(tag=='\n') tag=getchar();
    if(tag!='0' && tag!='1'){
        return NULL;
    }
    WORD * p = (WORD*)malloc(sizeof(WORD));
    if(!p) exit(OVERFLOW); p->tag = tag-'0';
    getchar(); scanf("%d",&(p->rlink)); getchar(); scanf("%d",&(p->size)); //getchar();
    return p;
}

Status Realease(WORD *pav){
    WORD * tem = pav;

    return OK;
}


int main(){
    WORD * pav;
    BuildList(&pav);
    printf("1done\n");
}
















