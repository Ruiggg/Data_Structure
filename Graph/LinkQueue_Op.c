#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "LinkQueue.h"

Status InitQueue(LinkQueue **Q){
    (*Q) = (LinkQueue *)malloc(sizeof(LinkQueue));
    if(!(*Q)) exit(OVERFLOW);
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode)); //the header node which dont store data
    if(!p) exit(OVERFLOW);
    p->next = NULL;
    (*Q)->head = (*Q)->rear = p;
    return OK;
}

Status DeQueue(LinkQueue *Q,QElemType *e){
    if(Q->head == Q->rear)  return ERROR; //check input
    QNode *p = Q->head->next; //the 1st node storing data
    *e = p->data; //e stores the int
    Q->head->next = p->next;
    if(p == Q->rear) Q->rear = Q->head; //if only on node storing data and it is to be deleted
    free(p);
    return OK;
}

Status EnQueue(LinkQueue *Q,QElemType e){
    QNode *p;
    p=(QNode *)malloc(sizeof(QNode));
    if(!p) return ERROR;
    p->data =e; p->next=NULL;
    Q->rear->next=p;
    Q->rear=p;
    return OK;
}

int IsQueueEmpty(LinkQueue *lq){
    if(lq->head == lq->rear) return 1;
    else return 0;
}






