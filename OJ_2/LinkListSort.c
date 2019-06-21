#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef struct LNode{
    int data;
    struct LNode * next;
}LNode,*LinkList;

Status InitLink(LinkList *l){
    LinkList p = (LinkList)malloc(sizeof(LNode));
    p->data=0; p->next=NULL;
    (*l) = p;
    return OK;
}

Status CreateLink(LinkList head){
    char c;
    if(!head) return ERROR;
    LinkList pre = head;
    do{
        int data;
        scanf("%d",&data);
        LinkList p = (LinkList)malloc(sizeof(LNode));
        if(!p) exit(OVERFLOW);
        p->data = data; p->next = NULL;
        pre->next = p;
        pre = p;
        c = getchar();
    }while(c!='\n');
    return OK;
}

Status Sort(LinkList L){
    LinkList firstNode = L->next;
    if(firstNode && firstNode->next){
        LinkList preNode = firstNode;
        LinkList sortingNode = firstNode->next;
        while(sortingNode){
            LinkList tem = NULL;
            if(sortingNode->data < preNode->data){
                tem = sortingNode;
                sortingNode = sortingNode->next;
                preNode->next = sortingNode;    //already be the next
                LinkList preP = L;
                LinkList curP = firstNode;
                for(;curP && curP->data <= tem->data;preP=curP,curP=curP->next) ;
                tem->next = curP;
                preP->next = tem;
                firstNode = L->next;
            }else{
                preNode = sortingNode;
                sortingNode = sortingNode->next;
            }
        }
    }
    return OK;
}

Status Show(LinkList L){
    LinkList cur;
    for(cur=L->next;cur;cur=cur->next){
        printf("%d",cur->data);
        if(cur->next) putchar(',');
    }
    return OK;
}

int main(){
    LinkList L;
    InitLink(&L);
    CreateLink(L);
    Sort(L);
    Show(L);
}





