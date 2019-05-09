#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED

typedef int QElemType;

typedef struct QNode {
    QElemType data;
    struct QNode * next;
}QNode,*QueuePtr;

typedef struct {
    QueuePtr head;
    QueuePtr rear;
}LinkQueue;


Status InitQueue(LinkQueue **Q);
Status EnQueue(LinkQueue *Q,QElemType e);
Status DeQueue(LinkQueue *Q,QElemType *e);
int IsQueueEmpty(LinkQueue *lq);


#endif // LINKQUEUE_H_INCLUDED
