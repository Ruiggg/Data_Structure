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

int inchars(char c,char* s){
    int k;
    for(k=0;s[k]!='\0';k++){
        if(s[k]==c)
            return 1;
    }
    return 0;
}

int SelectChar(HString T1,HString T2,char *result,char *pos){
    int i,j=0;
    for(i=0;i<T1.length;i++){
        if(!inchars(T1.ch[i],T2.ch))
        {
            if(!inchars(T1.ch[i],result)){
                pos[j]=i+'0';
                result[j]=T1.ch[i],j++;
                result[j]='\0';
            }
        }
    }
    result[j]=pos[j]='\0';
    if(j==0)return -1;
    return 1;
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
    char result[100];
    char pos[100];
    result[0]=pos[0]='\0';
    m=SelectChar(T1,T2,result,pos);
    ClearString(&T1);
    ClearString(&T2);
    if(m==-1)
        printf("%d",-1);
    else{
        printf("%s",result);
        printf(" ");
        printf("%s",pos);
    }
    return 0;
}
