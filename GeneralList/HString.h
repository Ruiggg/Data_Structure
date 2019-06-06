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
Status HStrAssign(HString *s,char *sc);
Status HStrConcat(HString *t,HString *s1,HString *s2);
Status HStrSubStr(HString *subs,HString *s,int pos,int len);
int CharAt(HString *s,char c);



#endif // HSTRING_H_INCLUDED
