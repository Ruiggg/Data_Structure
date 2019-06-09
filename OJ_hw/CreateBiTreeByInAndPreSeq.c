#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3

typedef char TElemType;
typedef int Status;


typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild,*rchild; //left and right sons
} BiTNode,*BiTree;


Status CreateBiTreeByPreInOrder(BiTree *root,int *pre,int pi,int pj,int *in,int ii,int ij){
    if((pj-pi)!=(ij-ii)) return ERROR;
    int rootv = pre[pi];
    int i;
    for(i=ii;i<ij;i++){
        if(rootv == in[i])
            break;
    }
    if(i>=ij) return ERROR;
    BiTree r = (BiTree)malloc(sizeof(BiTNode));
    r->data = rootv; r->lchild = NULL; r->rchild = NULL;
    (*root) = r;
    if(pj-pi==1) return OK;
    CreateBiTreeByPreInOrder(&((*root)->lchild),pre,pi+1,pi+i-ii+1,in,ii,i);
    CreateBiTreeByPreInOrder(&((*root)->rchild),pre,pi+i-ii+1,pj,in,i+1,ij);
    return OK;
}

Status ReadArray(int *pre,int *in){
    int n,i;
    for(i=0;i<100;i++){
        scanf("%d",&n);
        pre[i] = n;
        char c = getchar();
        if(c==';') break;
    }
    pre[i+1] = -1;
    for(i=0;i<100;i++){
        scanf("%d",&n);
        in[i] = n;
        char c = getchar();
        if(c=='\n') break;
    }
    in[i+1] = -1;
    return OK;
}
int numOfNodes = 0,in=0;
Status printInt(TElemType n){
    printf("%d",n);
    in++;
    if(in!=numOfNodes) putchar(',');
    return OK;
}


Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e)){
    if(T){
        if(PostOrderTraverse(T->lchild,Visit))
            if(PostOrderTraverse(T->rchild,Visit)) //don't forget this step
                if(Visit(T->data))
                    return OK;
        return ERROR;
    }
    return OK;
}

Status CreateAndPostTra(){
    BiTree T;
    int pre[100]; int in[100];
    ReadArray(pre,in);
    int last;
    for(last=0;pre[last]!=-1;last++);
    numOfNodes = last;
    CreateBiTreeByPreInOrder(&T,pre,0,last,in,0,last);
    PostOrderTraverse(T,printInt);
    return OK;
}



int main(){
    //OJ_addThrInOder();
    testOJ();
}

void testOJ(){
    //OJ_PreTra();
    /**
    BiTree T;
    CreateBiTree_OJ_LevelTra_ch(&T);
    InOrderTraverse_OJ(T,PrintElement,0);*/
    CreateAndPostTra();
}
