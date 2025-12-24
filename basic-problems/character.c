//Check whether a character is vowel or consonant; 
// if it's vowel: print 1, if it's consonant: print 0, and if anything else: print -1.

#include<stdio.h>
int main(){
    char ch='A';
    int res;
    if(ch>='A' && ch<='Z')
    {
        if(ch=='A'|| ch=='E'|| ch=='I'|| ch=='O'|| ch=='U')
            res=1;
        else
            res=0;
    }
    else{
        res=-1;
    }
    printf("%d",res);
}

/*you can contribute by 
1. writing a program that takes user input
2. works both for uppercase and lowercase
*/