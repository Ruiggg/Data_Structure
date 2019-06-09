#ifndef BITREE_H_INCLUDED
#define BITREE_H_INCLUDED
//about



// about Threaded Binary Tree
typedef enum PointerTag {Link,Thread} PointerTag;
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode * lchild,*rchild;
    PointerTag  LTag,RTag;
}BiThrNode,*BiThrTree;
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T);
void InThreading(BiThrTree p, BiThrTree *pre);
Status InOrderTraverse_Thr(BiThrTree T,Status(*Visit)(TElemType e));
Status CreateThrBiTree(BiThrTree *T);



typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild,*rchild; //left and right sons
} BiTNode,*BiTree;





Status CreateBiTree(BiTree *T);
Status PrintElement(TElemType e);
Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e));
Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e));
Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e));
Status InOrderTraverse_NR1(BiTree T,Status(*Visit)(TElemType e));
Status InOrderTraverse_NR2(BiTree T,Status(*Visit)(TElemType e));
Status PostOrderTraverse_NR(BiTree T,Status(*Visit)(TElemType e));

//OJ
Status CreateBiTree_OJ_LevelTra(BiTree *T);
Status CreateBiTree_OJ_LevelTra_ch(BiTree *T);
Status PreOrderTraverse_NR(BiTree T);
Status OJ_PreTra();
Status InOrderTraverse_OJ(BiTree T,Status(*Visit)(TElemType e),int tag);
Status OJ_addThrInOder();
Status CreateAndPostTra();





//about stack
typedef BiTree SElemType;
typedef struct Stack {
    SElemType * base;
    SElemType * top;
    int stacksize;
}SqStack;
Status InitStack(SqStack * S);
Status Push(SqStack *S,SElemType e);
Status Pop(SqStack *S,SElemType *e);
int StackEmpty(SqStack S);
Status GetTop(SqStack S,SElemType *e);


//other test
Status FindPOScr_IOThr(BiThrTree T, BiThrNode* p,BiThrNode **successor);
Status CheckFPOSIOT(BiThrTree T);
Status FindPostOrderFirst_Thr(BiThrTree T, BiThrNode ** p);
Status FindInOrderParent_Thr(BiThrTree T, BiThrNode ** parent, BiThrNode *p);
Status FindPostOrderFirst_Thr_NR(BiThrTree T, BiThrNode ** p);

#endif // BITREE_H_INCLUDED
