#include<stdio.h>


int getMaxRepSubstr(char *str,char *sub){
    int i;
    int pos[2];
    int len[2];
    char ch[2];
    pos[0]=pos[1]=0;
    len[1]=0,len[0]=1;
    ch[1]=ch[0]=str[0];

    for(i=0;str[i]!='\0';i++){
        if(ch[1]==str[i]){
            len[1]++;
            if(len[1]>=len[0])
                len[0]=len[1],ch[0]=ch[1],pos[0]=i-len[1]+1;
        }else{
            ch[1]=str[i];
            len[1]=1;
            pos[1]=i;
        }
    }
    for(i=0;i<len[0];i++){
        sub[i] = ch[0];
    }
    sub[i] = '\0';
    return pos[0];
}

int main(){
    char str[100];
    scanf("%s",str);
    char sub[100];
    sub[0] = '\0';

    int pos;
    pos = getMaxRepSubstr(str,sub);
    //printf("%d",pos);
    printf("%s %d",sub,pos);
    return 0;
}
