#include "Predefined_const.h"
#include "MPNode.h"
#include <stdio.h>
#include <stdlib.h>

Status InitMP(MPlist *p){
    (*p) = (MPlist)malloc(sizeof(MPNode));
    if(!(*p)) exit(OVERFLOW);
    (*p)->tag = 1;
    (*p)->exp = 0;
    //(*p)->hp =
    (*p)->tp = NULL;
    return OK;
}

Status CreateMP(MPlist p){
    return OK;
}

Status PrintMP(MPlist p,int varnum){
    // p is not the header of all , but the head of the fisrt layer(the head contains a variable)
    //because we will call this function recursively
    //int index = p->exp; //var nums
    //int index = varnum;
    //char c = p->exp;    //c is varible's symbol
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
            if(node->exp==0) ;
            else if(node->exp!=1) printf("(x_%d)^%d",varnum,node->exp);
            else printf("x_%d",varnum);
        }else{
            printf("+");PrintMP(node->hp,varnum-1);
            if(node->exp==0) ;
            else if(node->exp!=1) printf("(x_%d)^%d",varnum,node->exp);
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

Status CopyMP(MPlist * target, MPlist source){
    //target and source are the head of all
    InitMP(target);
    (*target)->tag = source->tag;
    (*target)->exp = source->exp;
    //(*target)->hp = source->hp;
    (*target)->tp = NULL;
    if(source->tag == 0){
        (*target)->coef = source->coef;
        return OK;
    }
    CopyMPrecursion(&( (*target)->hp ),source->hp);
    return OK;
}

Status CopyMPrecursion(MPlist* t , MPlist s){
    //the **t is the head containing an variable, not the whole head
    //copy *s to **t
    if(s){
         (*t) = CreateMPNode(s->tag,s->exp);
        if(s->tag==1)   (*t)->coef  = s->coef;
        else   {printf("a head's tag should always be 1\n"); return ERROR;}
        //(*t)->hp = s->hp;
        //(*t)->tp = s->tp;
        //copy the other list
        MPlist node = s->tp;
        MPlist tpre = *t;
        while(node){
            MPlist l = CreateMPNode(node->tag,node->exp);
            l->tp = NULL;
            tpre->tp = l;
            tpre = l;
            if(node->tag==1){ //list node
                CopyMPrecursion(&(l->hp),node->hp);
            }else if(node->tag==0){
                l->coef = node->coef;
            }
            node = node->tp;
        }
    }
    return OK;
}

Status DestroyMP(MPlist p){
    if(!p){printf("Error: p should be the whole head!\n"); return ERROR;}
    //destroy p->hp
    DestroyMPrecursion(p->hp);
    free(p);
    return OK;
}

Status DestroyMPrecursion(MPlist p){
    // p is the head containing a variable
    if(p){
        MPlist node = p->tp;
        free(p);
        while(node){
            if(node->tag==1){
                DestroyMPrecursion(node->hp);
                MPlist next = node->tp;
                free(node);
                node = next;
            }else{
                MPlist next = node->tp;
                free(node);
                node = next;
            }//if-else
        }//while
    }//if
    return OK;
}

Status DerivativeFisrtVar(MPlist *t,MPlist s){
    //calculate fisrt partial Derivative for the first(outermost) variable
    CopyMP(t,s);
    MPlist l = (*t)->hp;
    if(l)
        DeriFisrtVarRecurion(l);
    return OK;
}

Status DeriFisrtVarRecurion(MPlist t){
    if(t){
        MPlist pre = t;
        MPlist node = t->tp;
        while(node){
            if(node->tag==1){
                NumberMultiply(node->hp,node->exp);

            }else{
                //tag==0
                node->coef *= node->exp;
            }

            if(node->exp == 0){
                free(node);
                pre->tp = NULL;
            }else
                node->exp--;

            pre = node;
            node = node->tp;
        }//while
    }//if
    return OK;
}

Status NumberMultiply(MPlist p,float m){
    //modify p to p*m
    //p is not the whole header but the head containing a variable
    if(p){
        MPlist l = p->tp;//the first item in the ploy
        while(l){
            if(l->tag==1){
                NumberMultiply(l->hp,m);
            }else{
                l->coef *= m;
            }//if-else
            l = l->tp;
        }//while
    }//if
    return OK;
}

Status AddMP(MPlist t,MPlist s){
    //t = t+s
    //t,s is not the whole head, but the one containing a variable in exp
    if(!t) CopyMPrecursion(&t,s);
    else if(!s) return OK;
    else{
        MPlist tpre = t;
        MPlist tnode = t->tp;
        MPlist snode = s->tp;
        if(!snode) {printf("\nError in AddMP!\n"); return ERROR;}
        while(tnode){
            //tackle the snode whose exp are bigger than the current tnode's exp
            while(snode && snode->exp > tnode->exp){
                MPlist copyOfSnode;
                CopyMP(&copyOfSnode,snode);
                copyOfSnode->tp = tpre->tp;
                tpre->tp = copyOfSnode;
                snode = snode->tp;
                tpre = copyOfSnode;
            }
            //if s is over
            if(!snode)  return OK;
            //if s is not over
            if(snode->exp == tnode->exp){
                if(tnode->tag==0 && snode->tag==0){//the coef is both a number
                    tnode->coef += snode->coef;
                }else if(tnode->tag==0 && snode->tag==1){   //tnode's coef is a number while snode isn't
                    tnode->tag = 1;
                    MPlist sum;
                    CopyMP(&sum,snode);
                    AddNumberMP(sum,tnode->coef);
                    sum->tp = tnode->tp;
                    tpre->tp = sum;
                }else if(tnode->tag==1 && snode->tag==0){   //snode's coef is a number while tnode isn't
                    AddNumberMP(tnode,snode->coef);
                }else{
                    AddMP(tnode->hp,snode->hp);
                }
                snode = snode->tp;
            }
            //next-tnode
            tpre = tnode;
            tnode = tnode->tp;
        }
        //
        while(snode && snode->exp < tpre->exp){
                MPlist copyOfSnode;
                CopyMP(&copyOfSnode,snode);
                copyOfSnode->tp = NULL;
                tpre->tp = copyOfSnode;
                snode = snode->tp;
        }
    }
    return OK;
}

Status AddNumberMP(MPlist t,double f){
    //t is the whole head
    if(!t) {printf("Error in AddNumberMP---t is null!\n"); return ERROR;}
    MPlist l = t->hp;
    if(l){//l is the sub head
        MPlist node = l->tp;
        MPlist pre = l;
        //find the node whose exp is 0 or who is null
        //assume exp is not increasing
        while(node && node->exp!=0){
            pre = node;
            node = node->tp;
        }
        //if this node's exp is not null, so its exp is 0
        if(node && node->exp==0){
            if(node->tag==0)//if also a number
                node->coef += f;
            else{//if a poly
                AddNumberMP(node,f);
            }
        }else if(!node){//if node is null, means none's exp is 0
            MPlist newl = CreateMPNode(0,0);
            newl->coef = f;
            newl->tp = NULL;
            pre->tp = newl;
        }
    }else{
        printf("Tag error.\n");
    }
    return OK;
}

Status PolyMultiply(MPlist *d,MPlist t,MPlist s){
    //d = t*s
    //t.s.d is not the whole head
    MPlist ddd = CreateMPNode(1,t->exp);
    //MPlist f = CreateMPNode(0,0);
    //ddd->tp = f;
    //f->coef = 0.0;
    //f->tp = NULL;
    //do
    MPlist tnode = t->tp;
    while(tnode){
        MPlist snode = s->tp;
        while(snode){
            if(snode->tag==0 && tnode->tag==0){
                MPlist node = CreateMPNode(0,snode->exp + tnode->exp);
                MPlist head = CreateMPNode(1,t->exp);
                head->tp = node;
                node->tp = NULL;
                node->coef = snode->coef * tnode->coef;
                AddMP(ddd,head);
            }else if(snode->tag==0 && tnode->tag==1){
                MPlist head = CreateMPNode(1,t->exp);
                MPlist node = CreateMPNode(1,snode->exp + tnode->exp);
                head->tp = node;
                node->tp = NULL;

                CopyMPrecursion(&(node->hp),tnode->hp);
                NumberMultiply(head,snode->coef);

                AddMP(ddd,head);
            }else if(snode->tag==1 && tnode->tag==0){
                MPlist head = CreateMPNode(1,s->exp);
                MPlist node = CreateMPNode(1,snode->exp + tnode->exp);
                head->tp = node;
                node->tp = NULL;

                CopyMPrecursion(&(node->hp),snode->hp);
                NumberMultiply(head,tnode->coef);

                AddMP(ddd,head);
            }else{
                MPlist head = CreateMPNode(1,s->exp);
                MPlist node = CreateMPNode(1,snode->exp + tnode->exp);
                head->tp = node;
                node->tp = NULL;

                PolyMultiply(&(node->hp),tnode->hp,snode->hp);
                AddMP(ddd,head);
            }
            snode = snode->tp;
        }
        tnode = tnode->tp;
    }
    *d = ddd;
    return OK;
}



