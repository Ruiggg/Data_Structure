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
        getchar(); scanf("%d",&(p->uplink)); getchar(); scanf("%d",&(p->size)); getchar();
        if(pre){
            pre->rlink = p;
            p->llink = pre;
        }else{
            (*pav) = p;
        }
        pre = p;
        //printf("\n* %d %d %d *\n",p->tag,p->uplink,p->size);
    }
    //getchar();
    pre->rlink = (*pav);
    (*pav)->llink = pre;
    return OK;
}

WORD* ReadaRow(){
    char tag = getchar(); //printf("ctag = %d\n",tag-' ');
    if(tag=='\n') tag=getchar(); //printf("ctag = %d\n",tag);
    if(tag!='0' && tag!='1'){
        return NULL;
    }
    WORD * p = (WORD*)malloc(sizeof(WORD));
    if(!p) exit(OVERFLOW); p->tag = tag-'0';
    getchar(); scanf("%d",&(p->uplink)); getchar(); scanf("%d",&(p->size)); //getchar();
    return p;
}

Status Realease(WORD *pav){
    //WORD * tem = pav;
    WORD * pre = pav->llink;
    WORD * cur = pav;
    WORD * toberelease;

    while((toberelease=ReadaRow())!=NULL){
        //printf("%d %d %d\n",toberelease->tag,toberelease->uplink,toberelease->size);

        int size = toberelease->size;
        int addr = toberelease->uplink;

        while(cur->uplink < addr){
            cur=cur->rlink; pre=pre->rlink;
            if(cur==pav) break;
        }
        //printf("%p\n",&cur);
        //printf("cur->size = %d\n",cur->size);
        if(cur->uplink==addr+size && pre->uplink+pre->size==addr){
            pre->rlink = cur->rlink;
            cur->rlink->llink = pre;
            pre->size += (size+cur->size);
        }else if(cur->uplink==addr+size){
            cur->size += size;
            cur->uplink = addr;
        }else if(pre->uplink+pre->size==addr){
            pre->size += size;
        }else{
            toberelease->tag = 0;
            toberelease->llink = pre;
            toberelease->rlink = cur;
            pre->rlink = toberelease;
            cur->llink = toberelease;
        }
        cur = pav;
        pre = pav->llink;
    }
    return OK;
}

Status Show(WORD * pav){
    WORD * cur = pav;
    do{
        printf("%d %d %d\n",cur->tag,cur->uplink,cur->size);
        cur = cur->rlink;
    }while(pav!=cur);
    return OK;
}

int main(){
    WORD * pav;
    BuildList(&pav);
    //printf("\ndone %d %d\n",pav->tag,pav->rlink->size);
    Realease(pav);
    Show(pav);
    return 0;
}




/*
0 10000 15000
0 31000 8000
0 59000 41000

1 30000 1000
1 40000 2000

*/











