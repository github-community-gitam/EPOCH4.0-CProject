#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 10
#define MAX_TEXT 200
#define MAX_NAME 50

struct Question {
    char question[MAX_TEXT];
    char options[4][MAX_TEXT];
    int correctAnswer; // 1-4
};

struct Quiz {
    char name[MAX_NAME];
    struct Question questions[MAX_QUESTIONS];
    int questionCount;
};

// Global variables
struct Quiz quizzes[5];
int quizCount = 0;

// Function prototypes
void displayMenu();
void teacherMode();
void studentMode();
void createQuiz();
void viewQuizzes();
void takeQuiz();
void clearInput();

int main() {
    // Load sample quiz
    strcpy(quizzes[0].name, "General Knowledge");
    quizzes[0].questionCount = 2;
    
    strcpy(quizzes[0].questions[0].question, "What is the capital of France?");
    strcpy(quizzes[0].questions[0].options[0], "London");
    strcpy(quizzes[0].questions[0].options[1], "Paris");
    strcpy(quizzes[0].questions[0].options[2], "Berlin");
    strcpy(quizzes[0].questions[0].options[3], "Madrid");
    quizzes[0].questions[0].correctAnswer = 2;
    
    strcpy(quizzes[0].questions[1].question, "Which programming language is this?");
    strcpy(quizzes[0].questions[1].options[0], "C");
    strcpy(quizzes[0].questions[1].options[1], "Java");
    strcpy(quizzes[0].questions[1].options[2], "Python");
    strcpy(quizzes[0].questions[1].options[3], "JavaScript");
    quizzes[0].questions[1].correctAnswer = 1;
    
    quizCount = 1;
    
    int choice;
    printf("=== QuizMaster Pro ===\n");
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        clearInput();
        
        switch (choice) {
            case 1:
                teacherMode();
                break;
            case 2:
                studentMode();
                break;
            case 3:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void displayMenu() {
    printf("\n=== Main Menu ===\n");
    printf("1. Teacher Mode\n");
    printf("2. Student Mode\n");
    printf("3. Exit\n");
    printf("Choose: ");
}

void teacherMode() {
    int choice;
    printf("\n=== Teacher Menu ===\n");
    printf("1. Create Quiz\n");
    printf("2. View All Quizzes\n");
    printf("3. Back\n");
    printf("Choose: ");
    scanf("%d", &choice);
    clearInput();
    
    switch (choice) {
        case 1:
            createQuiz();
            break;
        case 2:
            viewQuizzes();
            break;
    }
}

void studentMode() {
    if (quizCount == 0) {
        printf("No quizzes available!\n");
        return;
    }
    takeQuiz();
}

void createQuiz() {
    if (quizCount >= 5) {
        printf("Maximum quiz limit reached!\n");
        return;
    }
    
    printf("Enter quiz name: ");
    fgets(quizzes[quizCount].name, MAX_NAME, stdin);
    quizzes[quizCount].name[strcspn(quizzes[quizCount].name, "\n")] = 0;
    
    printf("Number of questions (max 10): ");
    scanf("%d", &quizzes[quizCount].questionCount);
    clearInput();
    
    if (quizzes[quizCount].questionCount > MAX_QUESTIONS) {
        quizzes[quizCount].questionCount = MAX_QUESTIONS;
    }
    
    for (int i = 0; i < quizzes[quizCount].questionCount; i++) {
        printf("\n=== Question %d ===\n", i + 1);
        printf("Enter question: ");
        fgets(quizzes[quizCount].questions[i].question, MAX_TEXT, stdin);
        quizzes[quizCount].questions[i].question[strcspn(quizzes[quizCount].questions[i].question, "\n")] = 0;
        
        for (int j = 0; j < 4; j++) {
            printf("Option %d: ", j + 1);
            fgets(quizzes[quizCount].questions[i].options[j], MAX_TEXT, stdin);
            quizzes[quizCount].questions[i].options[j][strcspn(quizzes[quizCount].questions[i].options[j], "\n")] = 0;
        }
        
        printf("Correct answer (1-4): ");
        scanf("%d", &quizzes[quizCount].questions[i].correctAnswer);
        clearInput();
    }
    
    quizCount++;
    printf("Quiz created successfully!\n");
}

void viewQuizzes() {
    if (quizCount == 0) {
        printf("No quizzes available.\n");
        return;
    }
    
    printf("\n=== Available Quizzes ===\n");
    for (int i = 0; i < quizCount; i++) {
        printf("%d. %s (%d questions)\n", i + 1, quizzes[i].name, quizzes[i].questionCount);
    }
}

void takeQuiz() {
    char studentName[MAX_NAME];
    int quizChoice, answer, score = 0;
    
    viewQuizzes();
    printf("Choose quiz (1-%d): ", quizCount);
    scanf("%d", &quizChoice);
    clearInput();
    
    if (quizChoice < 1 || quizChoice > quizCount) {
        printf("Invalid quiz selection!\n");
        return;
    }
    
    quizChoice--; // Convert to 0-based index
    
    printf("Enter your name: ");
    fgets(studentName, MAX_NAME, stdin);
    studentName[strcspn(studentName, "\n")] = 0;
    
    printf("\n=== Starting Quiz: %s ===\n", quizzes[quizChoice].name);
    
    for (int i = 0; i < quizzes[quizChoice].questionCount; i++) {
        printf("\nQ%d: %s\n", i + 1, quizzes[quizChoice].questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, quizzes[quizChoice].questions[i].options[j]);
        }
        
        printf("Your answer (1-4): ");
        scanf("%d", &answer);
        clearInput();
        
        if (answer == quizzes[quizChoice].questions[i].correctAnswer) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong! Correct answer was %d.\n", quizzes[quizChoice].questions[i].correctAnswer);
        }
    }
    
    printf("\n=== Quiz Finished ===\n");
    printf("Student: %s\n", studentName);
    printf("Score: %d/%d\n", score, quizzes[quizChoice].questionCount);
    printf("Percentage: %.1f%%\n", (float)score / quizzes[quizChoice].questionCount * 100);
}

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}