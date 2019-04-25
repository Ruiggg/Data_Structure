#ifndef TREES_H_INCLUDED
#define TREES_H_INCLUDED

//parent-hoard-format
#define MAX_TREE_SIZE 100
typedef struct PTNode { //node
    TElemType data;
    int parent;
} PTNode;

typedef struct {    //tree
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;    //the position of root and the number of nodes
}PTree;


//children-chian-hoard-format
typedef struct CTNode {
    int child;  //the position of this child in the array
    struct CTNode * next;
}CTNode, *ChildPtr;

typedef struct {
    TElemType data;
    //int parent;
    ChildPtr firstchild;
} CTBox;

typedef struct {
    CTBox nodes[MAX_TREE_SIZE];
    int n,r;    //the number of nodes and the position of root
}Ctree;

//child-sibling hoard format
typedef struct CSNode {
    TElemType data;
    //struct CSNode * parent;
    struct CSNode * fisrtchild,*nextsibling;
}CSNode,*CSTree;


#endif // TREES_H_INCLUDED
