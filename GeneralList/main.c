#include <stdio.h>
#include <stdlib.h>
#include "Predefined_const.h"
#include "MPNode.h"
#include "GeneralList.h"
#include "HString.h"
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
/*
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
*/

void testdeleteValue(){
    GList_th l,t;
    InitGlist_th(&l,1);
    CreateTestGL_th(l);
    PrintGL_th(l);
    printf("\n");
    CopyGlist_th(&t,l);
    PrintGL_th(t);
    puts("");


    DeleteNode_GL_th(&t,'b');
    PrintGL_th(t);
    puts("");
}

int main(){
    /*
    GList_l l,t;
    InitGlist_l(&l);
    CreateTestGL_l(l);
    PrintGL_l(l); puts("");
    CopyGlist_l(&t,l);
    PrintGL_l(t); puts("");
    InsertFirst_GL_l(t,'g');
    PrintGL_l(t); puts("");
    DeleteNode_GL_l(t,'c');
    PrintGL_l(t); puts(""); */
    //testdeleteValue();
    //int d = GList_l_depth(t);
    //printf("Depth of t: %d\n",d);
    test_oj();
    return 0;
}



int test_oj(){
    char x = getchar();
    getchar();
    HString s; HStrInit(&s); char c; int i=0;
    while((c=getchar())!='\n'){
        s.ch[i++] = c;
    }
    s.length = i;
    GList_th g;

    GList_th * l = &g;
    Read_GList_th(l,&s);

    ;
    DeleteNode_GL_th_OJ(l,x);

    PrintGL_th_OJ(*l);
    return OK;
}
