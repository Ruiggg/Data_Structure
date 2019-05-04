#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "MPNode.h"
#include "GeneralList.h"
/*
int main()
{
    MPlist p;
    p=CreateMPNode(1,2);
    CreateTestMP(p);
    PrintMP(p->hp,2);
    return 0;
}
*/
/*
int main(){

    MPlist m,t;
    InitMP(&m);
    CreateTestMP(m);
    PrintMP(m->hp,2);
    //CopyMP(&t,m);
    printf("\n");
    DerivativeFisrtVar(&t,m);
    PrintMP(m->hp,2);
    printf("\n");
    PrintMP(t->hp,2);
    AddMP(t->hp,m->hp);
    printf("\n");
    PrintMP(t->hp,2);
    printf("\n");
    MPlist d;
    PolyMultiply(&d,t->hp,m->hp);
    PrintMP(d,2);
    DestroyMP(t);

    return 0;
}
*/

int main(){
    GList_th l,t;
    InitGlist_th(&l,1);
    CreateTestGL_th(l);
    //int d1 = GListDepth(l);
    //int d2 = GList_th_depth(l);
    //printf("d1=%d, d2=%d\n",d1,d2);
    PrintGL_th(l);
    printf("\n");
    CopyGlist_th(&t,l);
    PrintGL_th(t);
    puts("");
    int len = GList_th_length(t);
    printf("length = %d\n",len);
    InsertFirst_GL_th(&t,'g');
    PrintGL_th(t);
    puts("");
    int x;

    DeleteNode_GL_th(&t,'b');
    PrintGL_th(t);
    puts("");
    return 0;
}
