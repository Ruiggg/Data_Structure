#include <stdio.h>
#include <stdlib.h>

void Read_PT(int *T){
    int c,i=0;
    int queue[100],head=0,tail=0;
    for(int g=0;g<100;g++) queue[g]=-1;
    int num;
    if(scanf("%d",&num)==1){
        queue[tail++] = num;
        char c = getchar();
        if(c==';') return;
    }else return;
    while(1){
        int n;
        int p = queue[head++];

        if(scanf("%d",&n)==1){

            queue[tail++] = n;
            T[n] = p;
            char c = getchar();
            if(c==';') return;
        }else{
            char c;
            while((c=getchar())!=',' && c!=';');
            if(c==';') return;
        }
        //read another node

        if(scanf("%d",&n)==1){
            queue[tail++] = n;
            T[n] = p;
            char c = getchar();
            if(c==';') return;
        }else{
            char c;
            while((c=getchar())!=',' && c!=';');
            if(c==';') return;
        }
    }
}


void OJ_Communal_Anc(){
    int T[100];
    for(int i=0;i<100;i++) T[i]=-1;
    Read_PT(T);
    int s1,s2;
    scanf("%d",&s1); getchar();
    scanf("%d",&s2);
    for(int i=s1;i!=-1;i=T[i]){
        for(int j=s2;j!=-1;j=T[j]){
            if(j==i) {printf("%d",i); return;}
        }
    }
}


int main(void){
    OJ_Communal_Anc();
}








