#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "LinkQueue.h"

Status InitQueue(LinkQueue **Q){
    (*Q) = (LinkQueue *)malloc(sizeof(LinkQueue));
    if(!(*Q)) exit(OVERFLOW);
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode)); //the header node which dont store data
    if(!p) exit(OVERFLOW);
    p->prior = NULL;
    p->next = NULL;
    (*Q)->head = (*Q)->rear = p;
    return OK;
}

Status DeQueue(LinkQueue *Q,QElemType *e){ //out the queue
    if(Q->head == Q->rear)  return ERROR; //check input
    *e = Q->head->data;
    Q->head = Q->head->next;
    return OK;
}

Status EnQueue(LinkQueue *Q,QElemType e){
    QNode *p;
    p=(QNode *)malloc(sizeof(QNode));
    if(!p) exit(OVERFLOW);
    p->data =e; p->next=NULL; p->prior=Q->head;

    Q->rear->next=p;
    Q->rear=p;
    return OK;
}

int IsQueueEmpty(LinkQueue *lq){
    if(lq->head == lq->rear) return 1;
    else return 0;
}






