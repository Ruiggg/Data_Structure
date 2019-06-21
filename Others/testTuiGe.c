#include <stdio.h>
#include <stdlib.h>


int main(){
    int len = 7;
    for(int i=0;i<len;i++) printf("%c",'a'+i);
    //pause("1");
    for(int i=0;i<len;i++) printf("%c",'\b');
    putchar('l');
}
