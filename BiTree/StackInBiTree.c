#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "BiTree.h"

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

Status GetTop(SqStack S,SElemType *e){
    *e = *(S.top-1);
    return OK;
}
