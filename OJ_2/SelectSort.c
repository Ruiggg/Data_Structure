#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    int data;
    struct LNode * next;
}LNode,* LinkList;

void ReadLink(LinkList L){
    char c;
    LinkList pre = L;
    do{
        int v;
        scanf("%d",&v);
        LinkList p = (LinkList)malloc(sizeof(LNode));
        p->next = NULL; p->data = v;
        pre->next = p;
        pre = p;
        c = getchar();
    }while(c!='\n');
}

void InitLink(LinkList *L){
    LinkList p = (LinkList)malloc(sizeof(LNode));
    if(!p) exit(-1);
    p->data = 0; p->next = NULL;
    (*L)=p;
}

void selectSort(LinkList L){
    if(L->next && L->next->next){
        LinkList firstPtr = L;
        while(1)
        {
            LinkList preMin = firstPtr;
            LinkList min = firstPtr->next;
            LinkList p = firstPtr->next->next;
            LinkList pre = firstPtr->next;
            while(p){
                if(p->data < min->data){
                    min = p;
                    preMin = pre;
                }
                pre = p;
                p = p->next;
            }
            preMin->next = min->next;
            min->next = firstPtr->next;
            firstPtr->next = min;
            firstPtr = min;
            if(firstPtr->next==NULL) break;
        }
    }
}

int main(void){
    LinkList L;
    InitLink(&L);
    ReadLink(L);
    selectSort(L);
    for(LinkList p=L->next;p;p=p->next){
        printf("%d",p->data);
        if(p->next) printf(",");
    }
    /*
    for(LinkList p=L->next;p;p=p->next){
        if(p->next && p->data > p->next->data){
            printf("\nhit bad trap\n");
            return 0;
        }
    }
    printf("\nhit good trap\n");
    */
    return 0;
}
