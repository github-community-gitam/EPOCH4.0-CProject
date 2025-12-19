
#include <stdio.h>

/* Function declarations */
int askQuestion(const char *question, const char *opt1, const char *opt2, int correct);

int main() {
    int score = 0;

    printf("=== QUIZ GAME ===\n");

    score += askQuestion(
        "What is 2 + 2?",
        "3",
        "4",
        2
    );

    score += askQuestion(
        "What is the capital of India?",
        "Delhi",
        "Mumbai",
        1
    );

    printf("\nYour Score: %d/2\n", score);

    return 0;
}

/* Function to display question and validate answer */
int askQuestion(const char *question, const char *opt1, const char *opt2, int correct) {
    int answer;

    printf("\n%s\n", question);
    printf("1) %s\n", opt1);
    printf("2) %s\n", opt2);
    printf("Your answer: ");

    if (scanf("%d", &answer) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return 0;
    }

    if (answer == correct) {
        printf("Correct!\n");
        return 1;
    } else {
        printf("Wrong answer.\n");
        return 0;
    }
}

