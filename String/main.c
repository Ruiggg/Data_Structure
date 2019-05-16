#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "SString.h"
#include "HString.h"

void testSStr(void){
    char* s1 = "Data ";
    char* s2 = "Structure";
    SString t,ss1,ss2;
    CreateSStr(&ss1,s1);
    CreateSStr(&ss2,s2);
    SStrConcat(t,ss1,ss2);
    PrintSStr(t);
    SString sub;
    if(!SStrSubStr(sub,t,6,9)) printf("error\n");
    else PrintSStr(sub);
    int p = SStrIndex(t,sub,1);
    printf("\nThe pos is %d.\n",p);
}

void testHStr(void){
    char *s1 = "Data ";
    char *s2 = "Structure";
    HString hs1,hs2,t,subs;
    HStrInit(&hs1);
    HStrInit(&hs2);
    HStrInit(&t);
    HStrInit(&subs);

    HStrAssign(&hs1,s1);
    printf("%d\n",hs1.length);
    printf("%s\n",hs1.ch);

    HStrAssign(&hs2,s2);
    printf("%d\n",hs2.length);
    printf("%s\n",hs2.ch);

    if(HStrConcat(&t,&hs1,&hs2)) printf("%s\n",t.ch);
    printf("len: %d\n",t.length);

    HStrSubStr(&subs,&t,5,9);
    printf("%s\n",subs.ch);

    HStrInsert(&t,9,&subs);
    printf("%s\n",t.ch);

}

int main(){
    //testSStr();
    testHStr();
    return 0;
}
