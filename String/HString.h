#ifndef HSTRING_H_INCLUDED
#define HSTRING_H_INCLUDED

#define INITSTRLEN 100
//The heap allocated string
//whose strsize is dynamic
typedef struct {
    char *ch;
    int length;
    int strsize;
}HString,*HStrPtr;

Status HStrInit(HString *s);
int HStrLen(HString* s);
Status IsStrEqual(HString *s,HString *t);
Status HStrComp(HString *s,HString *t);
Status HStrAssign(HString *s,char *sc);
Status HStrConcat(HString *t,HString *s1,HString *s2);
Status HStrSubStr(HString *subs,HString *s,int pos,int len);
Status HStrInsert(HString *s,int i,HString *t);
Status HStrReplace(HString *s,int pos,int len,HString *t);
int HStrIndex(HString *s,HString *t,int pos);
Status HStrRepSubstr(HString *s,HString *t,HString *v);
int CharAt(HString *s,char c);

//KMP
Status getNext(HString *pattern,int *next);






#endif // HSTRING_H_INCLUDED
