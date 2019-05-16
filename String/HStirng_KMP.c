#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Predefined_const.h"
#include "HString.h"


Status getNext(HString *pattern,int *next){
    int k=-1,j=0;//index
    next[0]=-1;
    while(j<pattern->length){
        if(k==-1 || pattern->ch[k]==pattern->ch[j]){
            k++; j++;
            next[j] = k;
        }else
            k = next[k];
    }
    return OK;
}

//pos is the index+1
int HStrIndexKMP(HString *s,HString *t,int pos){ //s:main t:pattern; return:index+1
    int j=0,i=pos-1;//index
    int next[t->length];
    getNext(t,next);
    while(i<s->length && j<t->length){
        if(j==-1 || t->ch[j]==s->ch[i]) i++,j++;
        else j=next[j];
    }
    if(j>=t->length) return i-t->length+1;//return index+1
    else return 0;
}














