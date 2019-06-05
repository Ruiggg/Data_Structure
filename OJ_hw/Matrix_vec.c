#include <stdio.h>
#include <stdlib.h>


void Read_Matrix(int *M,int m,int n,int *vec){
    int iv = 0;
    getchar();
    for(int i=0;i<m;i++){
        getchar();
        for(int j=0;j<n;j++){
            scanf("%d",&(M[i*n+j])); getchar();
            if(M[i*n+j]!=0){vec[iv++]=M[i*n+j]; M[i*n+j]=1;}
        }
        getchar();
    }
}

void Print_Matrix(int *M,int m,int n){
    //printf("m=%d,n=%d",m,n);
    printf("[");

    for(int i=0;i<m;i++){
        printf("[");
        for(int j=0;j<n;j++){
            printf("%d",M[i*n+j]);
            if(j<n-1) printf(",");
        }
        printf("]");
        if(i<m-1) printf(";");
    }

    printf("]");
}


void Print_Vec(int *V,int size){
    int x = V[0],i=0;
    putchar('[');
    for(;x!=0 && i<size;i++,x=V[i]){
        printf("%d",V[i]);
        if(i+1<size && V[i+1]!=0) printf(",");
    }
    putchar(']');
}

int main(){
    int m,n;
    scanf("%d",&m); getchar();
    scanf("%d",&n); getchar();
    int size = m*n;
    int vec[size];
    int M[size];
    for(int i=0;i<size;i++) vec[i]=0;
    Read_Matrix(M,m,n,vec);
    Print_Vec(vec,size);
    printf(";");
    Print_Matrix(M,m,n);
    return 0;
}

