
#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "GeneralList.h"
#include "MPNode.h"



Status HStrInit(HString *s){
    if(!s) return ERROR;
    s->ch = (char *)malloc(INITSTRLEN*sizeof(char));
    s->length = 0;
    s->strsize = INITSTRLEN;
    return OK;
}

Status HStrAssign(HString *s,char *sc){
    int i=0;
    //get the length of sc --- to i
    while(sc[i]) i++;

    if(i >= s->strsize){
        s->ch = (char*)realloc(s->ch,(i+1)*sizeof(char));
        if(!s->ch) return ERROR;
        s->strsize = i+1;
    }
    s->length = i;
    for(i=0;i<s->length;i++)
        (s->ch)[i] = sc[i];
    (s->ch)[i] = '\0';
    return OK;
}


Status HStrConcat(HString *t,HString *s1,HString *s2){
    if(s1->length + s2->length >= t->strsize){
        t->ch = (char *)realloc(t->ch,(s1->length + s2->length + 1)*sizeof(char));
        if(!(t->ch)) return ERROR;
        t->strsize = s1->length + s2->length+1;
    }

    strncpy(t->ch,s1->ch,s1->length);
    strncpy(t->ch + s1->length,s2->ch,s2->length);
    t->length = s1->length + s2->length;
    t->ch[t->length] = '\0';
    return OK;
}


//POS :index not the sequential number
Status HStrSubStr(HString *subs,HString *s,int pos,int len){
    //pos is the index
    if(pos<0 || pos>=s->length || len<0 || len>s->length-pos) return ERROR;

    if(len >= subs->strsize){
        subs->ch = (char*)realloc(subs->ch,(len+1)*sizeof(char));
        if(!subs->ch) return ERROR;
        subs->ch = len+1;
    }

    int i;
    for(i=0;i<len;i++) subs->ch[i] = s->ch[i+pos];
    subs->length = len;
    subs->ch[len] = '\0';
    return OK;
}


//return index
int CharAt(HString *s,char c){
    int i=0;
    for(;i<s->length;i++){
        if(s->ch[i]==c) return i;
    }
    return -1;
}
