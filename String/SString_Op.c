#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Predefined_const.h"
#include "SString.h"

int SStrConcat(SString *t,SString *s1,SString *s2){
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
































