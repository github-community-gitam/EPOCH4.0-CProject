#include <stdio.h>

int main() {
    char ch;
    int res;

    // Take user input
    printf("Enter a character: ");
    scanf(" %c", &ch);   // space before %c avoids newline issues

    // Check if character is an alphabet (uppercase or lowercase)
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {

        // Check for vowels (both cases)
        if (ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U' ||
            ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u')
            res = 1;   // vowel
        else
            res = 0;   // consonant
    }
    else {
        res = -1;      // not an alphabet
    }

    printf("%d\n", res);

    return 0;
}
