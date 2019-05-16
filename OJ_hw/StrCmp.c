#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
typedef struct {
    char *ch;
    int length;
}HString;

int StrAssign(HString *T,char *chars){
    if(T->ch)
        free(T->ch);
    int i;
    char *c;
    for(i=0,c=chars;*c;i++,c++)
        ;
    if(!i){
        T->ch = NULL;
        T->length = 0;
    }else{
        if(!(T->ch = (char*)malloc(i*sizeof(char))))
            exit(OVERFLOW);
        T->length = i;
        for(;i>0;i--)
            T->ch[i-1] = chars[i-1];
    }
    return 1;
}

int ClearString(HString *S){
    if(S->ch){
        free(S->ch);
        S->ch = NULL;
        S->length = 0;
    }
    return 1;
}

int StrCompare(HString *S,HString *T){
    int i;
    for(i=0;i<S->length && i<S->length ;i++)
        if(S->ch[i]!=T->ch[i])
            return S->ch[i]-T->ch[i];
    return S->length - T->length;
}

int main(void){
    int m;
    char s[100];
    char t[100];
    scanf("%s",s);
    scanf("%s",t);
    HString T1,T2;
    T1.ch = T2.ch =NULL;
    StrAssign(&T1,s);
    StrAssign(&T2,t);
    m = StrCompare(&T1,&T2);
    ClearString(&T1);
    ClearString(&T2);
    if(m>0)
        printf("%d",1);
    else if(m==0)
        printf("%d",0);
    else
        printf("%d",-1);
    return 0;
}
