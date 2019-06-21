#include <stdio.h>
#include <stdlib.h>


int main(){
    int bucket[3];
    for(int s=0;s<3;s++) bucket[s]=0;
    char c;
    do{
        int v;
        scanf("%d",&v);
        bucket[v]++;
        c = getchar();
    }while(c!='\n');
    int buf[100]; int top=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<bucket[i];j++) {
            buf[top++] = i;
        }
    }
    for(int i=0;i<top;i++){
        printf("%d",buf[i]);
        if(i<top-1) putchar(',');
    }
    return 0;
}


