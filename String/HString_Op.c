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


//pos >= 1
Status HStrReplace(HString *s,int pos,int len,HString *t){
    //replace s: pos-1,pos,...,pos+len-2 with t
    //pos-1 is the index of pos-th char
    //pos=1,2,...,s->length; len=1,....,length-pos+1
    if(pos<=0 || pos>s->length || len<=0 || len>s->length-pos+1) return ERROR;
    if(len<t->length){
        if(s->strsize <= s->length+t->length-len){
            s->ch = (char*)realloc(s->ch,(s->length+t->length-len+1)*sizeof(char));
            if(!s->ch) return ERROR;
            s->strsize = s->length+t->length-len+1;
        }
        int shift = t->length - len; //move right  number
        for(int index=s->length;index>=pos-1+len;index--) s->ch[index+shift]=s->ch[index];
        //for(int index=pos-1;index<pos-1+t->length;index++) s->ch[index]=t->ch[index-(pos-1)];
    }else if(len>t->length){
        int shift = len-t->length; //move left
        for(int index=pos-1+t->length;index<=s->length;index++) s->ch[index]=s->ch[index+len-t->length];
    }
    for(int index=pos-1;index<pos-1+t->length;index++) s->ch[index]=t->ch[index-(pos-1)];
    s->length = s->length+t->length-len;
    return OK;
}


//pos >= 1
int HStrIndex(HString *s,HString *t,int pos){
    //from pos-1, match t in s
    //pos means pos-th char, that is, the index is pos-1
    //return the sequential number (=index+1)
    if(pos<=0||pos>s->length) return ERROR;//pos=1,2,...,s->length
    int i=pos-1;//i is index
    HString sub;
    HStrInit(&sub);
    while(i <= s->length - t->length){
        if(!HStrSubStr(&sub,s,i,t->length)) return ERROR;
        if(IsStrEqual(&sub,t)) return i+1;
        else i++;
    }
    return 0;
}

Status HStrRepSubstr(HString *s,HString *t,HString *v){
    //replace all t in s to v
    int pos = 1;
    while(pos<=s->length-t->length+1){
        int pos_sub = HStrIndex(s,t,pos);
        if(pos_sub==0) pos++;
        else HStrReplace(s,pos_sub,t->length,v),pos+=v->length;
    }
    return OK;
}





























