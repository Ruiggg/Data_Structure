#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;


int ReadArray(int *A,int len){
    int i = 0;
    while(i<len){
        int data;
        scanf("%d",&data);
        A[i++]=data;
        char c = getchar();
        if(c=='\n') break;
    }
    return i;
}

void Swap(int *A,int i,int j){
   int tem=A[i]; A[i]=A[j]; A[j]=tem;
}

void CmpSort(int *A,int start,int end){
    //printf("%d %d",start,end);
    if(end-start==1){
        if(A[start]>A[end]){
            Swap(A,start,end);
        }
    }else if(end-start==2){
        if(A[start]<=A[start+1] && A[start]<=A[start+2]){
            CmpSort(A,start+1,start+2);
        }else if(A[start]<=A[start+1] && A[start]>=A[start+2]){
            Swap(A,start,start+2);
            Swap(A,start+1,start+2);
        }else if(A[start]>=A[start+1] && A[start+2]>=A[start]){
            Swap(A,start,start+1);
        }else{
            if(A[start+1]<A[start+2]){
                Swap(A,start,start+1);
                Swap(A,start+1,start+2);
            }else{
                Swap(A,start,start+2);
            }
        }
    }
}


Status myqsort(int *A,int len){
    int stack[100],top=0;
    stack[top++]=0; stack[top++]=len-1;
    int start=0,end=0;
    //printf("first top=%d\n",top);
    while(top>0){
        end = stack[--top];
        start = stack[--top];
        if(end-start+1<=3){
            //printf("hit\n");
            CmpSort(A,start,end);
            continue;
        }
        int key = A[end];
        int begining = start;
        int ending = end;
        while(begining < ending){
            while(begining<ending && A[begining]<=key) begining++;
            while(ending>begining && A[ending]>=key) ending--;
            if(begining!=ending) Swap(A,begining,ending);
        }
        if(begining!=end) Swap(A,begining,end);
    //printf("ddd  %d\n",A[0]);
        int len1 = begining-start;
        int len2 = end-begining;
        if(len1<len2){
            stack[top++] = begining+1;
            stack[top++] = end;
            stack[top++] = start;
            stack[top++] = begining-1;
        }else{
            stack[top++] = start;
            stack[top++] = begining-1;
            stack[top++] = begining+1;
            stack[top++] = end;
        }
    }
}

int main(){
    int A[100];
    int len = ReadArray(A,100);
    //printf("l = %d\n",len);
    myqsort(A,len);
    //CmpSort(A,0,len-1);
    for(int i=0;i<len;i++){
        printf("%d",A[i]);
        if(i<len-1) putchar(',');
    }
    /*
    for(int i=0;i<len-1;i++){
        if(A[i]>A[i+1]){
            printf("\nHit bad trap.\n");
            return 0;
        }
    }
    printf("\nHit good trap.\n");
    */
    return 0;
}

