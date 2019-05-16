#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Predefined_const.h"
#include "SString.h"

Status CreateSStr(SString *t,char *s){
    int i;
    for(i=0;s[i] && i<MAXSTRLEN;i++) (*t)[i+1] = s[i];
    (*t)[0]=i;
    return OK;
}

int SStrConcat(SString t,SString s1,SString s2){
    int uncut;
    if(s1[0]+s2[0]<MAXSTRLEN){
        strncpy(t+1,s1+1,s1[0]);
        strncpy(t+s1[0]+1,s2+1,s2[0]);
        t[0] = s1[0]+s2[0];
        t[t[0]+1] = '\0';
        uncut = TRUE;
    }else if(s1[0]<MAXSTRLEN){ //only s2 is cut
        strncpy(t+1,s1+1,s1[0]);
        strncpy(t+s1[0]+1,s2+1,MAXSTRLEN-s1[0]);
        t[0] = MAXSTRLEN;
        t[MAXSTRLEN+1] = '\0';
        uncut = FALSE;
    }else{ //s1 is cut, no s2
        strncpy(t+1,s1+1,MAXSTRLEN);
        t[0] = MAXSTRLEN;
        t[MAXSTRLEN+1] = '\0';
        uncut = FALSE;
    }
    return uncut;
}

Status SStrSubStr(SString sub,SString s,int pos,int len){
    //pos,pos+1,...,pos+len-1
    //compose a substring
    if(pos<1 || pos>s[0] || len<0 || len>s[0]-pos+1) return ERROR;
    strncpy(sub+1,s+pos,len);
    sub[0]=len;
    sub[len+1]='\0';
    return OK;
}

int SStrIndex(SString s,SString t,int pos) {
    //main str: s
    //pattren str: t
    //return the position of the 1st char
    if(pos<1||pos>s[0]) return ERROR;
    int i=pos,j=1;
    while(i<=s[0] && j<=t[0]){
        if(s[i]==t[j]) i++,j++;
        else i=i-j+2,j=1;
    }
    if(j>=t[0]) return i-t[0];
    return 0;
}

Status PrintSStr(SString s){
    for(int i=1;i<=s[0];i++) printf("%c",s[i]);
    printf("\n");
    return OK;
}




























