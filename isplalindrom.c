#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef struct QNode {
    char data;
    struct QNode * next;
    struct QNode * ahead;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue *Q){
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q->front) exit(OVERFLOW);
    Q->front->next = NULL;
    Q->front->ahead = NULL;
    return OK;
}
Status DestroyQueue(LinkQueue *Q){
    while(Q->front){
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

Status EnQueue(LinkQueue *Q,char e){
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    p->ahead = Q->rear;
    Q->rear = p;
    return OK;
}
Status DeQueueF(LinkQueue *Q){
    QueuePtr tem = Q->front;
    Q->front = Q->front->next;
    free(tem);
    return OK;
}

Status DeQueueR(LinkQueue *Q){
    QueuePtr tem = Q->rear;
    Q->rear = Q->rear->ahead;
    free(tem);
    return OK;
}

int ispla(void){
    LinkQueue lq;
    InitQueue(&lq);
    char c;
    while((c=getchar())!='@'){
        EnQueue(&lq,c);
    }
    if(lq.front->next == lq.rear) return 1;
    while(lq.front->next==NULL || (lq.front!=lq.rear && lq.front->next != lq.rear)){
        if(lq.front->next->data == lq.rear->data){
            DeQueueF(&lq);
            DeQueueR(&lq);
        }
        else
        {
            DestroyQueue(&lq);
            return 0;
        }
    }
    DestroyQueue(&lq);
    return 1;
}

int main(){
    int result = ispla();
    printf("%d",result);
    return 0;
}
