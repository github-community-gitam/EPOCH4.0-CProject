// Check whether a character is vowel or consonant
// if it's vowel: print 1, if it's consonant: print 0, and if anything else: print -1

#include <stdio.h>

int main() {
    char ch;
    printf("Enter a character: ");
    scanf("%c", &ch);
    
    int result;
    
    // Check if character is an alphabet (fixed the bug: ch<='b' should be ch<='z')
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
        // Check if vowel
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ||
            ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            result = 1; // Vowel
        } else {
            result = 0; // Consonant
        }
    } else {
        result = -1; // Not an alphabet
    }
    
    printf("%d\n", result);
    return 0;
}