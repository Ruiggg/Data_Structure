#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef int ElemTag; //0:elemnode 1:list
typedef int Status;

#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0
#define INFEASIBLE  -1
#define OVERFLOW    -2
#define UNDERFLOW   -3

#define INITSTRLEN 100
//The heap allocated string
//whose strsize is dynamic
typedef struct {
    char *ch;
    int length;
    int strsize;
}HString,*HStrPtr;

Status HStrInit(HString *s){
    if(!s) return ERROR;
    s->ch = (char *)malloc(INITSTRLEN*sizeof(char));
    s->length = 0;
    s->strsize = INITSTRLEN;
    return OK;
}

Status HStrAssign(HString *s,char *sc){
    int i=0;
    //get the length of sc --- to i
    while(sc[i]) i++;

    if(i >= s->strsize){
        s->ch = (char*)realloc(s->ch,(i+1)*sizeof(char));
        if(!s->ch) return ERROR;
        s->strsize = i+1;
    }
    s->length = i;
    for(i=0;i<s->length;i++)
        (s->ch)[i] = sc[i];
    (s->ch)[i] = '\0';
    return OK;
}


Status HStrConcat(HString *t,HString *s1,HString *s2){
    if(s1->length + s2->length >= t->strsize){
        t->ch = (char *)realloc(t->ch,(s1->length + s2->length + 1)*sizeof(char));
        if(!(t->ch)) return ERROR;
        t->strsize = s1->length + s2->length+1;
    }

    strncpy(t->ch,s1->ch,s1->length);
    strncpy(t->ch + s1->length,s2->ch,s2->length);
    t->length = s1->length + s2->length;
    t->ch[t->length] = '\0';
    return OK;
}


//POS :index not the sequential number
Status HStrSubStr(HString *subs,HString *s,int pos,int len){
    //pos is the index
    if(pos<0 || pos>=s->length || len<0 || len>s->length-pos) return ERROR;

    if(len >= subs->strsize){
        subs->ch = (char*)realloc(subs->ch,(len+1)*sizeof(char));
        if(!subs->ch) return ERROR;
        subs->ch = len+1;
    }

    int i;
    for(i=0;i<len;i++) subs->ch[i] = s->ch[i+pos];
    subs->length = len;
    subs->ch[len] = '\0';
    return OK;
}


//return index
int CharAt(HString *s,char c){
    int i=0;
    for(;i<s->length;i++){
        if(s->ch[i]==c) return i;
    }
    return -1;
}


typedef int ElemType;
typedef int Status;

#define ATOM 0
#define LIST 1

typedef int Atomtype;   //int can be changed

//using head and tail storation format
//empty list pointer == NULL
typedef struct GLNode_th {
    ElemTag tag;// int
    union {
        Atomtype atom;
        struct {struct GLNode_th *hp,*tp;} ptr; //ptr.hp points to head, ptr.tp points to tail
    };
} GLNode_th,*GList_th;


Status DeleteNode_GL_th_OJ(GList_th *l,ElemType x);
Status DeleteNode_GL_th_OJ_recur(GList_th *l,ElemType x,GList_th *pre);

Status DeleteNode_GL_th_OJ(GList_th *l,ElemType x){
    GList_th * pre = NULL;
    DeleteNode_GL_th_OJ_recur(l,x,pre);
    return OK;
}


Status DeleteNode_GL_th_OJ_recur(GList_th *l,ElemType x,GList_th *pre){
    //delete nodes whose value is x
    if(*l){

        if((*l)->tag==LIST){
            if((*l)->ptr.hp!=NULL){
                if((*l)->ptr.hp->tag==ATOM && (*l)->ptr.hp->atom==x){

                    (*l) = (*l)->ptr.tp;
                    DeleteNode_GL_th_OJ_recur(l,x,NULL);
                    //DeleteNode_GL_th_OJ_recur(&( (*l)->ptr.tp ),x,l);
                }else{
                    DeleteNode_GL_th_OJ_recur(&( (*l)->ptr.hp ),x,NULL);
                    DeleteNode_GL_th_OJ_recur(&( (*l)->ptr.tp ),x,l);
                }
            }
        }
    }
    return OK;
}



Status InitGlist_th(GList_th * p,ElemTag t){
    //e is a
    (*p) = (GList_th)malloc(sizeof(GLNode_th));
    if(!(*p)) exit(OVERFLOW);
    (*p)->tag = t;
    if(t==LIST){
        ((*p)->ptr).hp = NULL;
        ((*p)->ptr).tp = NULL;
    }else{
        ((*p)->atom)=0;
    }
    return OK;
}

Status PrintGL_th(GList_th l){
    if(l){
        if(l->tag == ATOM){
            printf("%2c",l->atom);
            return OK;
        }
        printf(" (");
        while(l){
            PrintGL_th(l->ptr.hp);
            l = l->ptr.tp;
        }
        printf(" )");
    }else{
        printf("()");
    }
    return OK;
}

Status PrintGL_th_OJ(GList_th l){
    if(!l){
        printf("()");
        return OK;
    }
    if(l->tag==ATOM){
        if(isalpha(l->atom))    printf("%c",l->atom);
        else    printf("%d",l->atom);
        return OK;
    }
    putchar('(');
    for(;l;l=l->ptr.tp){
        PrintGL_th_OJ(l->ptr.hp);
        if(l->ptr.tp!=NULL) printf(",");
    }
    putchar(')');
    return OK;
}


int findAnother(HString *s,int pos){
    int i;
    char stack[100]; int top = 0;
    for(i=pos;i<s->length;i++){
        if(s->ch[i]=='(')  stack[top++]='(';
        if(s->ch[i]==')'){
            if(top>=1 && stack[top-1]=='(') {
                top--;
                if(top==0) return i;
            }
        }
    }
    return -1;
}

Status Read_GList_th(GList_th *l,HString *s){
    char c = s->ch[0];
    //printf("1:c = %c\n",c);
    if(c=='('){
        if(s->length == 1) return ERROR;
        InitGlist_th(l,LIST);
        char hc = s->ch[1];//(,char,)
        //printf("2:hc = %c\n",hc);

        if(hc=='('){
            //int index = CharAt(s,')');
            int index = findAnother(s,1);
            if(index==-1) return ERROR;

            HString subs;
            HStrInit(&subs);
            HStrSubStr(&subs,s,1,index);
            Read_GList_th( &((*l)->ptr.hp),&subs ); //head

            HString s1; HStrInit(&s1);
            s1.ch[0]='('; s1.ch[1]='\0'; s1.length = 1;
            HString s2; HStrInit(&s2);

            if(s->ch[index+1]==')'){
                HStrSubStr(&s2,s,index+1,1);
            }else{
                if(HStrSubStr(&s2,s,index+2,s->length - index - 2)!=OK) return ERROR;
            }

            HString t; HStrInit(&t);
            HStrConcat(&t,&s1,&s2);
            //printf("t=%s\n",t.ch);

            Read_GList_th( &((*l)->ptr.tp),&t );   //tail
        }else if(hc==')'){ //end
            (*l) = NULL;
        }else{
            HString ss1;
            HStrInit(&ss1); ss1.length=0;
            //(ss1.ch)[0]=hc; (ss1.ch)[1]='\0'; ss1.length=1;
            int nextpos = CharAt(s,',');
            if(nextpos==-1) {
                nextpos = CharAt(s,')');
            }
            HStrSubStr(&ss1,s,1,nextpos-1);
            ss1.ch[nextpos-1] = '\0';
            //printf("hc=%c,ss1=%s\n",hc,ss1.ch);


            if(Read_GList_th( &((*l)->ptr.hp),&ss1 )!=OK) return ERROR;
            if(s->length==2) return ERROR;

            HString s1; HStrInit(&s1);
            s1.ch[0]='('; s1.ch[1]='\0'; s1.length = 1;
            //create s2
            HString s2; HStrInit(&s2);
            if(s->ch[nextpos]==',')
                HStrSubStr(&s2,s,nextpos+1,s->length-(nextpos+1));
            else
                HStrSubStr(&s2,s,nextpos,1);
            //concat
            HString t; HStrInit(&t);
            HStrConcat(&t,&s1,&s2);
            Read_GList_th( &((*l)->ptr.tp),&t );

        }
    }else{
            InitGlist_th(l,ATOM);
            int j; char elem = 0;
            if(!isdigit(c)){
                (*l)->atom = c;
                return OK;
            }
            elem = atoi(s->ch);
            (*l)->atom = elem;
    }
    return OK;
}


char Read_Token(){
    char c = getchar();
    if(!isdigit(c)){
        getchar();
        return c;
    }else{
        int num = c-'0';
        c= getchar();
        while(isdigit(c)){
            num = num*10 + (c-'0');
            c = getchar();
        }
        return num;
    }
}


int main(){
    char x = Read_Token();
    HString s; HStrInit(&s); char c; int i=0;
    while((c=getchar())!='\n'){
        s.ch[i++] = c;
    }
    s.ch[i] = '\0';
    s.length = i;

    GList_th g;
    GList_th * l = &g;

    Read_GList_th(l,&s);
    DeleteNode_GL_th_OJ(l,x);
    PrintGL_th_OJ(*l);
    return OK;
}
