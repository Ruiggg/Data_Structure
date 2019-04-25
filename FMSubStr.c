#include<stdio.h>

int main(void){
    char str[50];
    scanf("%s",str);
    int i,j,pos=0,len=0,max=0,k=0;
    for(i=0;str[i]!='\0';i++){
        for(j=i+1;str[j]!='\0';j++){
            for(k=0,len=0;str[j+k]!='\0';k++){
                if(str[i+k]==str[j+k] && i+k<j)
                    len++;
                else{
                    break;
                }
            }
            if(len>max){
                max = len;
                pos = i;
            }
        }
    }
    if(max!=0){
        str[pos+max]='\0';
        printf("%s %d",str+pos,pos);
    }
    else
        printf("%d",max-1);
    return 0;
}
