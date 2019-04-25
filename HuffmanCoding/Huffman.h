#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#include "Predefined_const.h"

typedef struct {
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char** HuffmanCode;    //array of pointers

Status Select(HuffmanTree HT,int up,int *s1,int *s2);
Status HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n);
Status PrintHuffmanCode(HuffmanCode HC,int n);
Status HuffmanCoding_UPD(HuffmanTree *HT,HuffmanCode *HC,int *w,int n);




#endif // HUFFMAN_H_INCLUDED
