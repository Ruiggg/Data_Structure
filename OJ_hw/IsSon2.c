#include <stdio.h>
#include <stdlib.h>

void Read_data(int *L,int *R){
    int num,i=0,c;
    do{
        scanf("%d",&num);
        L[i++] = num;
    }while((c=getchar())!=';');
    L[i]=-1;
    i = 0;
    do{
        scanf("%d",&num);
        R[i++] = num;
    }while((c=getchar())!=';');
    R[i]=-1;
}

int main(){
    int L[101];
    int R[101];
    int T[101];
    Read_data(L,R);

    int son,parent;
    scanf("%d",&son); getchar();
    scanf("%d",&parent);
    for(int i=0;i<101;i++) T[i] = 0;
    for(int i=0;i<101 && L[i]!=-1;i++){
        if(L[i]) T[L[i]] = i;
        if(R[i]) T[R[i]] = i;
    }
    int node = T[son];

    while(node){
        if(node==parent){putchar('1'); return 0;}
        else node = T[node];
    }
    putchar('0');
    return 0;
}
