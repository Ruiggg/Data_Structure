#include <stdio.h>
#include <stdlib.h>



#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3

#define FootLoc(p) p+p->size-1
typedef int Status;

typedef struct WORD {
    int startAddr;
    int size;
    struct WORD * next;
}WORD;

int main(){
    int cellsize;
    int lowbound,highbound;
    scanf("%d",&lowbound); getchar(); scanf("%d",&highbound); getchar(); scanf("%d",&cellsize); getchar();
    int i;
    int numOfCell = (highbound-lowbound)/cellsize;
    WORD * pav = NULL;
    WORD * pre = NULL;
    int flag = 1;
    for(i=0;i<numOfCell;i++){
        int tag;
        scanf("%d",&tag); getchar();
        WORD * p;
        if(tag==0 && flag==1){
            flag = 0;
            p = (WORD*)malloc(sizeof(WORD));
            p->next = NULL;
            p->size = cellsize;
            p->startAddr = i*cellsize+lowbound;
            if(!pre){
                pav = p;
                pre = p;
            }
            else{
                pre->next = p;
                pre = p;
            }
        }else if(tag==0 && flag==0){
            pre->size += cellsize;
        }else
            flag = 1;
    }
    WORD * p;
    for(p=pav;p;p=p->next){
        printf("%d %d %d\n",0,p->startAddr,p->size);
    }
    if(!pav) puts("0 0 0");
}






