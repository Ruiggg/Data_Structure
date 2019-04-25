Status InitArray(Array *A,int dim,...){
    if(dim<1 || dim>MAX_ARRAY_DIM)
        return(ERROR);      //the bad parameter : return ERROR
    A->dim = dim;
    A->bounds = (int *)malloc(dim*sizeof(int));
    if(!(A->bounds))
        exit(OVERFLOW);     //can not malloc memory: "EXIT"(overflow), take care of the difference

    int elemtotal = 1;
    va_list ap;
    va_start(ap,dim);
    int i,b;
    //calulate bounds array and the total number(stored in "elemtotal") of elements
    for(i=0;i<dim;i++){
        //b is the elements numbers in each dimension
        b = va_arg(ap,int);
        //there can have no elements, so b can't less than 0 rather than 1
        if(b<0)
            return UNDERFLOW;
        elemtotal *= b;
        (A->bounds)[i] = b;
    }
    va_end(ap);

    A->base = (ElemType *)malloc(elemtotal*sizeof(ElemType));
    if(!A->base)
        exit(OVERFLOW);

    A->constants = (int *)malloc(sizeof(int));
    if(!(A->constants))
        exit(OVERFLOW);

    (A->constants)[dim-1] = 1;
    //using the formula derived in the textbook (Page 93)
    for(i=dim-2;i>=0;i--){
        (A->constants)[i] = (A->constants)[i+1] * (A->bounds)[i+1];
    }

    return OK;
}

Status DestroyArray(Array *A){
    if(!(A->base))          //we must confirm the ptr is not NULL, for we can't free a NULL ptr
        return ERROR;       //there still returns ,not exit(exit only malloc failed)
    free(A->base);
    A->base = NULL;         //after fring it, don't forget to set it to value NULL

    if(!A->bounds)          // "->" > "!"
        return ERROR;
    free(A->bounds);
    A->bounds = NULL;

    if(!A->constants)
        return ERROR;
    free(A->constants);
    A->constants = NUL;

    return OK;
}

Status Locate(Array A, va_list ap, int *off){
    //to find the offset from A->base[0]
    //and store it in off
    int i,offset,j;
    offset = 0;
    for(i=0; i<A.dim ;i++){
        j = va_arg(ap,int);
        if(b<0)
            return UNDERFLOW;
        offset += (j * (A.constants[i]));
    }
    *off = offset;
    return OK;
}

Status Value(Array A,ElemType *e,...){

    //A:array
    //e:value to be stored
    //...: the n index of the value
    //to store the value of A[j1]...[jn] to e
    va_list ap;
    va_start(ap,e);
    int offset,result;
    if((result=Locate(A,ap,&offset)) <= 0)
        return result;          //Thus we can tranfer the return value to the former function//better than return ERROR
    //else
    *e = A.base[offset];
    return OK;
}

Status Assign(Array *A, ElemType *e,...){
    va_list ap;
    va_start(ap,e);
    int result,offset;
    if((result=Locate(A,ap,&offset)) <= 0)
        return result;
    //else
    (*e) = (A->base)[offset];
    return OK;
}
