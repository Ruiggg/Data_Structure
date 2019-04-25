#ifndef SQ_ARRAY_H_INCLUDED
#define SQ_ARRAY_H_INCLUDED

#include <stdarg.h>

#define MAX_ARRAY_DIM 8

typedef int ElemType;   //"int/char" can be converted to another data type"
typedef struct {
    ElemType *base;     //the base address of the array, allocated by the "InitArray" function
    int dim;            //the dimension of the array
    int *bounds;        //the base address of the array, which documetates the max element number of each dimension
    int *constants;
}Array;

#endif // SQ_ARRAY_H_INCLUDED
