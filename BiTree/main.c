#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "BiTree.h"

/*
int main()
{
    BiThrTree T,Thr;
    CreateThrBiTree(&T);
    InOrderThreading(&Thr,T);
    //InOrderTraverse_Thr(Thr,PrintElement);
    CheckFPOSIOT(T);
    BiTree T;
    CreateBiTree(&T);
    PostOrderTraverse_NR(T,PrintElement);
    printf("\n");
    PostOrderTraverse(T,PrintElement);
    return 0;
}
*/

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
