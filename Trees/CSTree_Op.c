#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Trees.h"

Status PreOrder(CSTree T,Status(*Visit)(TElemType e)){
    //eaual to the preorder of bitree
    if(T){
        if((Visit(T->data))) return ERROR;
        CSTree p;
        for(p=T->fisrtchild;p;p=p->nextsibling){
            PreOrder(p,Visit);
        }
    }
    return OK;
}

Status PostOrder(CSTree T,Status(*Visit)(TElemType e)){
    //equivalent to the InOrder of Bitree
    if(T){
        CSTree p;
        for(p=T->fisrtchild;p;p=p->nextsibling){
            PreOrder(p,Visit);
        }
        if((Visit(T->data))) return ERROR;
    }
    return OK;
}

















