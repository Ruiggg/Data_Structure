#ifndef LSTRING_H_INCLUDED
#define LSTRING_H_INCLUDED
//block-chain hoard format


#define CHUNKSIZE 8

typedef struct Chunk{
    char ch[CHUNKSIZE];
    struct Chunk * next;
}Chunk;

typedef struct {
    Chunk * head;
    Chunk * tail;
    int curLen; //the number of nodes
}LString;

#endif // LSTRING_H_INCLUDED
