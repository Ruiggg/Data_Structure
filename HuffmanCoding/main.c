#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "Huffman.h"


int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int w[5]={3,1,1};
    int n = 3;
    HuffmanCoding(&HT,&HC,w,n);
    PrintHuffmanCode(HC,n);
    HuffmanCoding_UPD(&HT,&HC,w,n);
    PrintHuffmanCode(HC,n);
    return 0;
}
