#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "SString.h"
#include "HString.h"
#include "LString.h"


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

    if(HStrReplace(&t,9,15,&hs1)) printf("%s\n",t.ch);
    printf("len: %d\n",t.length);

    int index = HStrIndex(&t,&hs1,3);
    printf("pos(index+1): %d\n",index);

    HStrRepSubstr(&t,&hs1,&hs2);
    printf("%s\n",t.ch);
}

void testKMP(void){
    //char *s1 = "Data Structure Data Structure";
    char *s1 = "abaabcac";
    HString hs1;
    HStrInit(&hs1);
    HStrAssign(&hs1,s1);
    int next[hs1.length];
    getNext(&hs1,next);
    for(int i=0;i<hs1.length;i++) printf("%4d",next[i]);
    printf("\n-------------------------------------------------------------\n");
    char *s3 = "acabaabaabcacaabc";
    HString mainstr;
    HStrInit(&mainstr);
    HStrAssign(&mainstr,s3);
    int pos = HStrIndexKMP(&mainstr,&hs1,1);
    printf("pos: %d\n",pos);
    pos = HStrIndexFastKMP(&mainstr,&hs1,1);
    printf("After fastKMP, pos: %d\n",pos);
}

int main(){
    //testSStr();
    //testHStr();
    testKMP();
    return 0;
}
