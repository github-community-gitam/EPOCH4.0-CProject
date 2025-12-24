//Check whether a character is vowel or consonant; 
// if it's vowel: print 1, if it's consonant: print 0, and if anything else: print -1.

#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main(){
    char word;
    printf("Enter the character:");
    scanf("%c",&word);
    word = tolower(word);
    if(isalpha(word)){
        if(word=='a' || word=='e' || word=='i' || word=='o' || word=='u'){
            printf("1\n");
        }
        else{
            printf("0\n");
        }
    }
    else{
        printf("-1\n");
    }
}

/*you can contribute by 
1. writing a program that takes user input
2. works both for uppercase and lowercase
*/