#include <stdlib.h>
#include <stdio.h>


#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int Status;
typedef struct Node{
    int value;
    struct Node * next;
}Node,*List;


Node * ReadList(){
    List firstNode = NULL;
    List preNode = NULL;
    char c;
    do{
        int v;
        scanf("%d",&v);
        Node * node = (List)malloc(sizeof(Node));
        if(!node) exit(OVERFLOW);
        node->value = v; node->next=NULL;
        if(!firstNode) firstNode=node,node->next=node;
        if(preNode) preNode->next = node,node->next=firstNode;
        preNode=node;
    }while((c=getchar())!=';');
    return firstNode;
}

Status SearchValue(List firstNode){

    char c;
    List firstPos = firstNode;
    do{
        int v;
        scanf("%d",&v);
        printf("%d",firstPos->value);

        if(v==firstPos->value) ;
        else if(v<firstPos->value){
            printf(",");
            for(firstPos=firstNode;firstPos->value!=v;firstPos=firstPos->next){printf("%d,",firstPos->value);}
            printf("%d",v);
        }else{
            printf(",");
            for(firstPos=firstPos->next;firstPos->value!=v;firstPos=firstPos->next){printf("%d,",firstPos->value);}
            printf("%d",v);
        }

        c=getchar();
        if(c==',') printf(";");
    }while(c!='\n');
}

int main(){
    List l = ReadList();
    SearchValue(l);
    return 0;
}

