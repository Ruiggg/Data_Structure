#ifndef MPNODE_H_INCLUDED
#define MPNODE_H_INCLUDED

typedef int ElemTag;

//the MPNode uses expanded storation format
typedef struct MPNode {
    ElemTag tag;
    int exp;    //exponent
    union {
        float coef; //coefficient ---element node, means the coefficient is a real number
        struct MPNode *hp; //or a header pointing to a node --- list node, the coef is another poly with other varibles
    };
    struct MPNode * tp; //pointing to next term in the same layer of the general list
} MPNode,*MPlist;

Status InitMP(MPlist p);
Status CreateMP(MPlist p);
Status PrintMP(MPlist p,int varnum);
Status CreateTestMP(MPlist p);
MPlist CreateMPNode(ElemTag t,int ex);

#endif // MPNODE_H_INCLUDED
