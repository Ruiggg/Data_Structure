#include "Predefined_const.h"
#include "MPNode.h"
#include <stdio.h>
#include <stdlib.h>

Status InitMP(MPlist p){
    if(p){
        //init p as a head node
        p->tag = 1;
        p->exp = 0; //var numbers
        p->hp=NULL;
        p->tp=NULL;
        return OK;
    }
    else
        return ERROR;
}

Status CreateMP(MPlist p){
    return OK;
}

Status PrintMP(MPlist p,int varnum){
    //int index = p->exp; //var nums
    int index = varnum;
    char c = p->exp;    //c is varible's symbol
    MPlist node = p->tp;
    printf("(");
    while(node){
        if(node->tag==0 && node==p->tp){
            printf("%.2f",node->coef);
            if(node->exp!=0) {
                if(node->exp != 1)
                    printf("(x_%d)^%d",varnum,node->exp);
                else
                    printf("x_%d",varnum);
            }
        }
        else if(node->tag==0){
            printf("+");printf("%.2f",node->coef);
            if(node->exp!=0) {
                if(node->exp != 1)
                    printf("(x_%d)^%d",varnum,node->exp);
                else
                    printf("x_%d",varnum);
            }
        }
        else if(node->tag!=0 && node==p->tp){
            PrintMP(node->hp,varnum-1);
            if(node->exp!=1) printf("(x_%d)^%d",varnum,node->exp);
            else printf("x_%d",varnum);
        }else{
            printf("+");PrintMP(node->hp,varnum-1);
            if(node->exp!=1) printf("(x_%d)^%d",varnum,node->exp);
            else printf("x_%d",varnum);
        }

    node = node->tp;
    }
    printf(")");
    return OK;
}

Status CreateTestMP(MPlist p){
    //(x_1^2+x_1)x_2^2 + (x_1^1)x_2 + 1
    p->tag=1; p->exp=2; p->tp=NULL; p->hp=NULL;
    MPlist ph = CreateMPNode(1,'x'); //haven't op its hp and tp
    p->hp=ph;
    MPlist p2 = CreateMPNode(1,2);
    ph->tp=p2;
    MPlist p3 = CreateMPNode(1,1);
    p2->tp=p3;
    MPlist p4 = CreateMPNode(0,0); p4->coef=1.0;
    p3->tp=p4;
    p4->tp=NULL;

    MPlist p2h = CreateMPNode(1,'y');
    p2->hp = p2h;
    MPlist p22 = CreateMPNode(0,2); p22->coef = 1.0;
    p2h->tp = p22;
    MPlist p23 = CreateMPNode(0,1); p23->coef = 1.0;
    p22->tp=p23;
    p23->tp=NULL;

    MPlist p3h = CreateMPNode(1,'y');
    p3->hp = p3h;
    MPlist p32 = CreateMPNode(0,1); p32->coef = 1.0;
    p3h->tp=p32;
    p32->tp=NULL;

    return OK;
}

MPlist CreateMPNode(ElemTag t,int ex){
    MPlist p = (MPlist)malloc(sizeof(MPlist));
    if(!p) exit(OVERFLOW);
    p->tag = t;
    p->exp = ex;
    return p;
}











