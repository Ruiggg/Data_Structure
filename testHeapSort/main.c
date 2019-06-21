#include <stdio.h>
#include <stdlib.h>

int ReadArray(int *A){
    int len = 0;
    char c;
    do{
        int data;
        scanf("%d",&data);
        A[len++] = data;
        c = getchar();
    }while(c!='\n');
    return len;
}

void Swap(int *A,int i,int j){
    int tem = A[i]; A[i]=A[j]; A[j]=tem;
}

int Parent(int i){
    int a = i+1;
    if(a%3==0 || a%3==1) return (a/3)-1;
    else return (a/3);
}

void percolateUp(int *Heap,int lenOfHeap){
    int i = lenOfHeap - 1;
    while(i>0){
        int j = Parent(i);
        if(Heap[i]>Heap[j]) Swap(Heap,i,j);
        i = j;
    }
}

void HeapCreate(int *Heap,int *A,int len){
    int i = 0;
    while(i<len){
        Heap[i] = A[i]; i++;
        percolateUp(Heap,i);
    }
}

int maxIndex(int *Heap,int i,int j,int k,int len){
    if(k>=len && j<len){
        if(Heap[i]>=Heap[j]) return i;
        else return j;
    }
    if(j>=len && i<len) return i;
    if(i>=len && j>=len && k>=len) return -1;
    if(Heap[i]>=Heap[j] && Heap[i]>=Heap[k]) return i;
    if(Heap[j]>=Heap[i] && Heap[j]>=Heap[k]) return j;
    if(Heap[k]>=Heap[i] && Heap[k]>=Heap[j]) return k;
    return -1;
}

void percolateDown(int *Heap,int len){
    int i = 0;
    while(i<len){
        int a = i+1;
        int j = maxIndex(Heap,3*a-2,3*a-1,3*a,len);
        if(j<0) break;
        if(Heap[i]<Heap[j]) Swap(Heap,i,j);
        i = j;
    }
}

void HeapSort(int *A,int len){
    int Heap[len];
    HeapCreate(Heap,A,len);
    for(int i=len-1;i>=0;i--){
        Swap(Heap,0,i);
        percolateDown(Heap,i);
    }
    for(int i=0;i<len;i++){
        printf("%d",Heap[i]);
        if(i<len-1) putchar(',');
    }
}


int main(){
    int A[100];
    int len = ReadArray(A);

    HeapSort(A,len);
}


