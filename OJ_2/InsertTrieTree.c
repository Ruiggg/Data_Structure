#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAX_PTR_NUM 26

#define BRANCH 0
#define LEAF   1

typedef int Status;

typedef struct TrieNode{
    int depth;
    int numOfWord;
    char ch;
    struct TrieNode * ptr[MAX_PTR_NUM];
}TrieNode, * TrieTree;

TrieNode * CreateTrieNode(int depth,char ch){
    TrieNode * p = (TrieNode*)malloc(sizeof(TrieNode));
    if(!p) exit(OVERFLOW);
    p->ch = ch;
    p->depth = depth;
    p->numOfWord = 0;
    for(int i=0;i<MAX_PTR_NUM;i++) p->ptr[i]=NULL;
    return p;
}

int OrderOfRecord(char c){
    return (c-'a');
}

Status InitTrieTree(TrieTree *T){
    (*T) = CreateTrieNode(0,'\0');
    return OK;
}

Status InsertWord(TrieTree T,char* word,int depth){
    int i;
    TrieTree p = T;
    for(int i=0;i<depth && word[i];i++){
        int index = OrderOfRecord(word[i]);
        if(p->ptr[index]) {
            p = p->ptr[index];
            if(p) p->numOfWord++;
        }else{
            TrieTree node = CreateTrieNode(p->depth+1,word[i]);
            node->numOfWord++;
            p->ptr[index] = node;
            p = node;
        }
    }
    return OK;
}

int nums[20];
int top=0;

Status Traverse(TrieTree T){
    if(!T) return OK;
    if(T->depth>0) nums[top++]=T->numOfWord;
    for(int i=0;i<MAX_PTR_NUM;i++){
        if(T->ptr[i]) {Traverse(T->ptr[i]);}
    }
    return OK;
}

Status DelWord(TrieTree T,char *word,int depth){
    int i;
    TrieTree p = T;
    TrieTree pre = NULL;
    for(i=0;i<depth && word[i];i++){
        char c = word[i];
        int index = OrderOfRecord(c);
        pre=p,p = p->ptr[index];
        if(p->numOfWord>1){
            p->numOfWord--;
        }else if(p->numOfWord==1){
            p->numOfWord--;
        }
    }
    return OK;
}

int main(){
    TrieTree T;
    InitTrieTree(&T);
    for(int i=0;i<20;i++) nums[i]=0;
    int depth;
    scanf("%d",&depth); getchar();
    char c;
    char tobedelete[10];
    do{
        char word[10]; int j=0;
        do{
            c = getchar();
            if(c<='z' && c>='a') word[j++] = c;
        }while(c!=';'&&c!='\n');
        word[j]='\0';
        if(c=='\n') {strncpy(tobedelete,word,j); tobedelete[j]='\0';}
        j=0;
        if(c!='\n') InsertWord(T,word,depth);
    }while(c!='\n');
    //printf("%s\n",tobedelete);
    DelWord(T,tobedelete,depth);
    Traverse(T);
    for(int i=0;i<top;i++){
        printf("%d",nums[i]);
        if(i<top-1) putchar(',');
    }
    return 0;
}


