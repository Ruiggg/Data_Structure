#ifndef SSTRING_H_INCLUDED
#define SSTRING_H_INCLUDED

//Static String --- space is fixed

#define MAXSTRLEN 255

typedef unsigned char SString[MAXSTRLEN+2];// SString;
typedef SString SString;
//s[0] is the length

Status CreateSStr(SString *t,char *s);
int SStrConcat(SString t,SString s1,SString s2);
Status SStrSubStr(SString sub,SString s,int pos,int len);
int SStrIndex(SString s,SString t,int pos);
Status PrintSStr(SString s);


#endif // SSTRING_H_INCLUDED
