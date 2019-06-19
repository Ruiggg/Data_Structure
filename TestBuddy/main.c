#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3
#define M 16

#define FootLoc(p) p+p->size-1
typedef int Status;

typedef struct WORD {
    struct WORD * llink;//former
    int uplink;
    struct WORD * rlink;//next
}WORD,*Space;
Status Create(Space List[M]){
    char k[10],c;
    int i=0;
    WORD * pre = NULL;
    while((c=getchar())>='0' && c<='9'){
        k[i++] = c;
        while((c=getchar())<='0' && c>='9'){
            k[i++] = c;
        }
        k[i] = '\0';
        int exp = atoi(k);
        while(c!='\n'){
            Space p = (Space)malloc(sizeof(WORD));
            if(!p) exit(OVERFLOW);

            scanf("%d",&(p->uplink));

            if(!pre){
                List[exp] = p;
                p->llink = NULL;
                p->rlink = NULL;
            }
            else{
                pre->rlink = p;
                p->llink = pre;
            }
            pre = p;
            c = getchar();
            if(c==EOF) return OK;
        }
        pre = NULL;
        i=0;
    }
    return OK;
}


typedef struct box {
    Space head;
    int exp;
}box;

int IsEnd = 0;

box* ReadaRow(){
    char ch = getchar();
    char num[10]; int i = 0;
    if(ch<'0'||ch>'9') return NULL;
    num[i++] = ch;
    while((ch=getchar())>='0' && ch<='9'){
        num[i++] = ch;
    }
    num[i] = '\0';
    int exp = atoi(num);

    Space p = NULL;
    Space hp;
    while(ch==' '){
        Space pre = p;
        p = (Space)malloc(sizeof(WORD));
        scanf("%d",&(p->uplink)); p->rlink = NULL;
        if(!pre) hp = p;
        else pre->rlink = p;
        ch = getchar();
        if(ch==EOF) IsEnd = 1;
        if(ch==EOF) puts("EOF in row end");


    }
    box * bp = (box*)malloc(sizeof(box));
    bp->exp = exp;
    bp->head = hp;
    return bp;
}

Status Insert(Space List[M],int exp,Space p){
    //TODO:
    Space firstWord = List[exp];
    p->llink = p->rlink = NULL;
    if(!firstWord) {List[exp] = p; return OK;}
    Space wordptr = firstWord;
    Space wordpre = NULL;
    for(;wordptr && wordptr->uplink<p->uplink;wordpre=wordptr,wordptr=wordptr->rlink);
    if(wordptr==firstWord){
        int buddyAddr;
        int tem1 = (1<<(exp+1));
        int tem2 = (1<<exp);

        if((p->uplink)%tem1==0) buddyAddr = p->uplink + tem2;
        else if((p->uplink)%tem1==tem2) buddyAddr = p->uplink - tem2;
        else {puts("\n\nerr in insert\n\n"); exit(ERROR);}

        if(buddyAddr==wordptr->uplink){
            List[exp]=wordptr->rlink;
            Insert(List,exp+1,p);
            return OK;
        }else{
            p->rlink = wordptr;
            wordptr->llink = p;
            List[exp] = p;
        }
    }else if(wordptr==NULL){
        int buddyAddr;
        int tem1 = (1<<(exp+1));
        int tem2 = (1<<exp);

        if((p->uplink)%tem1==0) buddyAddr = p->uplink + tem2;
        else if((p->uplink)%tem1==tem2) buddyAddr = p->uplink - tem2;
        else {puts("\n\nerr in insert\n\n"); exit(ERROR);}

        if(wordpre->uplink==buddyAddr){
            if(wordpre==List[exp]){
                List[exp]=wordpre->rlink;
                Insert(List,exp+1,wordpre);
            }
            else{
                wordpre->llink->rlink=NULL;
                Insert(List,exp+1,wordpre);
            }
            return OK;
        }else{
            wordpre->rlink = p;
            p->llink = wordpre;
            return OK;
        }
    }else{
        int buddyAddr;
        int tem1 = (1<<(exp+1));
        int tem2 = (1<<exp);

        if((p->uplink)%tem1==0) buddyAddr = p->uplink + tem2;
        else if((p->uplink)%tem1==tem2) buddyAddr = p->uplink - tem2;
        else {puts("\n\nerr in insert\n\n"); exit(ERROR);}

        if(buddyAddr==wordpre->uplink){
            if(wordpre==List[exp]){
                List[exp]=wordpre->rlink;
                Insert(List,exp+1,wordpre);
            }
            else{
                wordpre->llink->rlink=wordpre->rlink;
                wordpre->rlink->llink = wordpre->llink;
                Insert(List,exp+1,wordpre);
            }
            return OK;
        }else if(buddyAddr==wordptr->uplink){
            wordpre->rlink = wordptr->rlink;
            if(wordptr->rlink!=NULL) wordptr->rlink->llink=wordpre;
            Insert(List,exp+1,p);
        }else{
            p->rlink = wordpre->rlink;
            p->llink = wordpre;
            wordpre->rlink=p;
            wordptr->llink=p;
        }
        return OK;
    }


    return OK;
}

Status release(Space List[M]){
    box *bp;
    while(IsEnd==0 && (bp=ReadaRow())!=NULL){

        int exp = bp->exp;
        Space hp = bp->head;
        //printf("\n*\n%d %d\n*\n",exp,hp->uplink);
        while(hp){
            int buddyAddr;
            int tem1 = (1<<(exp+1));
            int tem2 = (1<<exp);

            if((hp->uplink)%tem1==0) buddyAddr = hp->uplink + tem2;
            else if((hp->uplink)%tem1==tem2) buddyAddr = hp->uplink - tem2;
            else {puts("\n\nerr\n\n"); exit(ERROR);}


            int flag = 0;
            for(Space p=List[exp];p && flag==0;p=p->rlink){
                if(p->uplink==buddyAddr){
                    flag = 1;
                    if(p==List[exp]){
                        List[exp]=p->rlink;
                        //Insert(List,exp+1,p);
                    }else if(p->rlink){
                        p->llink->rlink = p->rlink;
                        p->rlink->llink = p->llink;
                        //Insert(List,exp+1,p);
                    }else if(p->rlink==NULL){
                        p->llink->rlink = p->rlink;
                    }
                    if(buddyAddr<hp->uplink) Insert(List,exp+1,p);
                    else Insert(List,exp+1,hp);
                }
            }
            if(!flag){
                //TODO:have no buddy, just insert accord to addr
                Space temp = (Space)malloc(sizeof(WORD));
                temp->uplink = hp->uplink;
                Insert(List,exp,temp);
            }
            hp = hp->rlink;
        }
    }
    return OK;
}

Status Show(Space List[M]){
    //TTODO
    for(int i=0;i<M;i++){
        if(List[i]){
            printf("%d ",i);
            Space p = List[i];
            for(;p;p=p->rlink){
                printf("%d",p->uplink);
                if(p->rlink) printf(" ");
                else printf("\n");
            }
        }
    }
    return OK;
}

int main()
{
    Space List[M];
    for(int i=0;i<M;i++) List[i]=NULL;
    Create(List);
    //release(List);
    Show(List);
    return 0;
}
