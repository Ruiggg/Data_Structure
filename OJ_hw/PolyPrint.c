#include <stdio.h>
#include <stdlib.h>


int Read_Matrix(int **M,int m,int n){

    if(m==1){
        getchar();//[
        for(int i=0;i<n;i++){
            scanf("%d",(*M)++);
            getchar();//; or ]
        }
    }else if(m>1){
        getchar();
        for(int i=0;i<n;i++){
            Read_Matrix(M,m-1,n);
            getchar();
        }
    }else
        return 0;
    return 1;
}

int Change_index(int m,int n,int index[]){
    int i;
    for(i=m-1;index[i]==0;i--);
    if(i<0) return 0;
    for(index[i]--,i++;i<m;i++){
        index[i] = n-1;
    }
    return 1;
}

int getInt(int M[],int index[],int m,int n){
    int c[m]; c[m-1]=1;
    for(int i=m-2;i>=0;i--) c[i]=c[i+1]*n;
    int offset = 0;
    for(int i=0;i<m;i++)
        offset += (c[i]*index[i]);
    //printf("\n***\n%d\n***\n",offset);
    return M[offset];
}

int Print_Poly(int **M,int m,int n,int index[],int isFirst){
    int co = getInt(*M,index,m,n);
    int flag = 1;
    for(int s=0;s<m && flag;s++){
        if(index[s]!=0)
            flag = 0;
    }
    if(co!=0){
        if(!isFirst) printf("+");
        if(co!=1 || flag) printf("%d",co);
        for(int i=1;i<=m;i++){
            if(index[i-1]!=0){
                printf("x%d",i);
                if(index[i-1]!=1)
                    printf("E%d",index[i-1]);
            }
        }
    }
    //change index
    if(Change_index(m,n,index)==0) return 1;

    if(isFirst && co==0){
        Print_Poly(M,m,n,index,isFirst);
    }else{
        Print_Poly(M,m,n,index,0);
    }
    return 1;
}

int main(){

    int **M;
    (M) = (int **)malloc(sizeof(int *));
    int m,n;
    scanf("%d",&m); //read dimension
    getchar();
    scanf("%d",&n); //read number of elements in each dimension
    getchar();

    int size = 1;
    for(int i=0;i<m;i++) size *= n;


    int *uuu = (int *)malloc(size * sizeof(int));
    //printf("???2");
    //exit(1);

    (*M) = uuu;
    if(!(*M)) {printf("Error!"); exit(1);}

    //printf("???2");
    //exit(1);


    int *t = *M;
    Read_Matrix(M,m,n);

/*
    for(int i=0;i<size;i++){
        printf("%3d",t[i]);
        if((i+1)%n==0) printf("\n");
    }
*/

    int index[m];
    for(int i=0;i<m;i++) index[i]=n-1;
    Print_Poly(&t,m,n,index,1);
    return 0;
}
