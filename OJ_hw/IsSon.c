#include <stdio.h>
#include <stdlib.h>

void Read_data(int *L,int *R){
    int num,i=0,c;
    do{
        scanf("%d",&num);
        L[i++] = num;
    }while((c=getchar())!=';');
    i = 0;
    do{
        scanf("%d",&num);
        R[i++] = num;
    }while((c=getchar())!=';');
}

int main(){
    int L[101];
    int R[101];
    Read_data(L,R);
    int son,parent;
    scanf("%d",&son); getchar();
    scanf("%d",&parent);
    int node = parent;
    int stack[100],top=0;
    stack[top++] = node;
    while(1){
        if(top>0) node = stack[--top];
        else {putchar('0');break;}
        if(L[node]==son || R[node]==son) {putchar('1');break;}
        else {
            if(L[node]) stack[top++] = L[node];
            if(R[node]) stack[top++] = R[node];
        }
    }
    return 0;
}
