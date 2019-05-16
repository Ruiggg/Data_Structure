#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Predefined_const.h"
#include "HString.h"

Status HStrInit(HString *s){
    if(!s) return ERROR;
    s->ch = (char *)malloc(INITSTRLEN*sizeof(char));
    s->length = 0;
    s->strsize = INITSTRLEN;
    return OK;
}

int HStrLen(HString* s){
    return s->length;
}

Status IsStrEqual(HString *s,HString *t){
    int i=0;
    while(i<s->length && i<t->length){
        if((s->ch)[i] == (t->ch)[i]) i++;
        else return FALSE;
    }
    if(s->length == t->length) return TRUE;
    else return FALSE;
}

Status HStrComp(HString *s,HString *t){
    int i=0;
    while(i<s->length && i<t->length){
        if((s->ch)[i] == (t->ch)[i]) i++;
        else return (s->ch)[i]-(t->ch)[i];
    }
    if(s->length == t->length) return TRUE;
    else return s->length - t->length;
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

Status HStrSubStr(HString *subs,HString *s,int pos,int len){
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

Status HStrInsert(HString *s,int i,HString *t){
    //insert t to s before i-th char
    //i = 1,2,...,length+1
    if(i<1 || i > s->length+1) return ERROR;
    if(s->strsize <= s->length + t->length){
        s->ch = (char*)realloc( s->ch,(s->length+t->length+1)*sizeof(char) );
        if(!s->ch) return ERROR;
        s->strsize = s->length + t->length + 1;
    }
    //shift
    int j;
    for(j=s->length-1;j>=i-1;j--) s->ch[j+(t->length)]=s->ch[j];
    for(j=0;j<t->length;j++) s->ch[j+i-1]=t->ch[j];
    s->length += t->length;
    return OK;

}




