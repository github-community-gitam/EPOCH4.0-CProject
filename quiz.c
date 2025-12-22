#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 50
#define MAX_QUESTION_TEXT 200
#define MAX_OPTION_TEXT 100
#define MAX_PLAYERS 20
#define FILENAME "quiz_data.txt"
#define SCORES_FILE "scores.txt"

struct Question {
    int id;
    char question[MAX_QUESTION_TEXT];
    char options[4][MAX_OPTION_TEXT];
    int correctAnswer; // 1-4
    char category[50];
    int difficulty; // 1-Easy, 2-Medium, 3-Hard
};

struct Player {
    char name[50];
    int score;
    int totalQuestions;
    float percentage;
};

// Function prototypes
void displayMenu();
int getChoice();
void startQuiz(struct Question *questions, int questionCount);
void addQuestion(struct Question *questions, int *questionCount);
void viewQuestions(struct Question *questions, int questionCount);
void editQuestion(struct Question *questions, int questionCount);
void removeQuestion(struct Question *questions, int *questionCount);
void searchQuestions(struct Question *questions, int questionCount);
void sortQuestions(struct Question *questions, int questionCount);
void viewScores();
void saveQuestions(struct Question *questions, int questionCount);
int loadQuestions(struct Question *questions);
void saveScore(struct Player player);
void clearInputBuffer();
void removeNewline(char *str);
void displayQuestion(struct Question q, int qNum);
void initializeDefaultQuestions(struct Question *questions, int *count);
int validateAnswer(int answer);

int main() {
    struct Question questions[MAX_QUESTIONS];
    int questionCount = 0;
    int choice;

    // Load existing questions or initialize defaults
    questionCount = loadQuestions(questions);
    if (questionCount == 0) {
        initializeDefaultQuestions(questions, &questionCount);
        printf("\n=== QUIZ GAME ===\n");
        printf("Initialized with %d default questions.\n", questionCount);
    } else {
        printf("\n=== QUIZ GAME ===\n");
        printf("Loaded %d existing questions.\n", questionCount);
    }

    while (1) {
        displayMenu();
        choice = getChoice();

        switch (choice) {
            case 1:
                startQuiz(questions, questionCount);
                break;
            case 2:
                addQuestion(questions, &questionCount);
                break;
            case 3:
                viewQuestions(questions, questionCount);
                break;
            case 4:
                editQuestion(questions, questionCount);
                break;
            case 5:
                removeQuestion(questions, &questionCount);
                break;
            case 6:
                searchQuestions(questions, questionCount);
                break;
            case 7:
                sortQuestions(questions, questionCount);
                break;
            case 8:
                viewScores();
                break;
            case 9:
                saveQuestions(questions, questionCount);
                printf("\nData saved successfully!\n");
                break;
            case 10:
                saveQuestions(questions, questionCount);
                printf("\nGoodbye! Data saved automatically.\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void displayMenu() {
    printf("\n==========================================\n");
    printf("              QUIZ GAME                  \n");
    printf("==========================================\n");
    printf("1. Start Quiz\n");
    printf("2. Add Question\n");
    printf("3. View All Questions\n");
    printf("4. Edit Question\n");
    printf("5. Remove Question\n");
    printf("6. Search Questions\n");
    printf("7. Sort Questions\n");
    printf("8. View High Scores\n");
    printf("9. Save Data\n");
    printf("10. Exit\n");
    printf("==========================================\n");
    printf("Enter your choice (1-10): ");
}

int getChoice() {
    int choice;
    while (scanf("%d", &choice) != 1) {
        printf("Invalid input! Please enter a number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return choice;
}

void startQuiz(struct Question *questions, int questionCount) {
    if (questionCount == 0) {
        printf("\nNo questions available for quiz!\n");
        return;
    }

    struct Player player;
    int answer, score = 0;
    
    printf("\n--- START QUIZ ---\n");
    printf("Enter your name: ");
    fgets(player.name, 50, stdin);
    removeNewline(player.name);
    
    printf("\nQuiz started! Answer the questions (1-4):\n");
    
    for (int i = 0; i < questionCount && i < 10; i++) { // Max 10 questions per quiz
        displayQuestion(questions[i], i + 1);
        
        do {
            printf("Your answer (1-4): ");
            scanf("%d", &answer);
            clearInputBuffer();
        } while (!validateAnswer(answer));
        
        if (answer == questions[i].correctAnswer) {
            printf("Correct!\n\n");
            score++;
        } else {
            printf("Wrong! Correct answer was %d.\n\n", questions[i].correctAnswer);
        }
    }
    
    int totalQuestions = (questionCount < 10) ? questionCount : 10;
    float percentage = (float)score / totalQuestions * 100;
    
    printf("\n==========================================\n");
    printf("           QUIZ COMPLETED!               \n");
    printf("==========================================\n");
    printf("Player: %s\n", player.name);
    printf("Score: %d/%d\n", score, totalQuestions);
    printf("Percentage: %.1f%%\n", percentage);
    
    if (percentage >= 80) printf("Grade: Excellent!\n");
    else if (percentage >= 60) printf("Grade: Good!\n");
    else if (percentage >= 40) printf("Grade: Average\n");
    else printf("Grade: Needs Improvement\n");
    
    // Save score
    player.score = score;
    player.totalQuestions = totalQuestions;
    player.percentage = percentage;
    saveScore(player);
}

void addQuestion(struct Question *questions, int *questionCount) {
    if (*questionCount >= MAX_QUESTIONS) {
        printf("\nMaximum question limit reached!\n");
        return;
    }

    struct Question newQ;
    newQ.id = *questionCount + 1;

    printf("\n--- ADD NEW QUESTION ---\n");
    
    printf("Enter question: ");
    fgets(newQ.question, MAX_QUESTION_TEXT, stdin);
    removeNewline(newQ.question);
    
    for (int i = 0; i < 4; i++) {
        printf("Enter option %d: ", i + 1);
        fgets(newQ.options[i], MAX_OPTION_TEXT, stdin);
        removeNewline(newQ.options[i]);
    }
    
    do {
        printf("Enter correct answer (1-4): ");
        scanf("%d", &newQ.correctAnswer);
        clearInputBuffer();
    } while (!validateAnswer(newQ.correctAnswer));
    
    printf("Enter category: ");
    fgets(newQ.category, 50, stdin);
    removeNewline(newQ.category);
    
    printf("Enter difficulty (1-Easy, 2-Medium, 3-Hard): ");
    scanf("%d", &newQ.difficulty);
    clearInputBuffer();
    
    questions[*questionCount] = newQ;
    (*questionCount)++;
    
    printf("\nQuestion added successfully!\n");
}

void viewQuestions(struct Question *questions, int questionCount) {
    if (questionCount == 0) {
        printf("\nNo questions available.\n");
        return;
    }
    
    printf("\n==========================================\n");
    printf("             ALL QUESTIONS               \n");
    printf("==========================================\n");
    
    for (int i = 0; i < questionCount; i++) {
        displayQuestion(questions[i], i + 1);
        printf("Correct Answer: %d | Category: %s | Difficulty: %d\n\n", 
               questions[i].correctAnswer, questions[i].category, questions[i].difficulty);
    }
}

void editQuestion(struct Question *questions, int questionCount) {
    if (questionCount == 0) {
        printf("\nNo questions to edit.\n");
        return;
    }
    
    int id;
    printf("\nEnter question ID to edit: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    for (int i = 0; i < questionCount; i++) {
        if (questions[i].id == id) {
            printf("\n--- EDITING QUESTION ID %d ---\n", id);
            displayQuestion(questions[i], 0);
            
            printf("\nEnter new question: ");
            fgets(questions[i].question, MAX_QUESTION_TEXT, stdin);
            removeNewline(questions[i].question);
            
            for (int j = 0; j < 4; j++) {
                printf("Enter new option %d: ", j + 1);
                fgets(questions[i].options[j], MAX_OPTION_TEXT, stdin);
                removeNewline(questions[i].options[j]);
            }
            
            do {
                printf("Enter new correct answer (1-4): ");
                scanf("%d", &questions[i].correctAnswer);
                clearInputBuffer();
            } while (!validateAnswer(questions[i].correctAnswer));
            
            printf("Enter new category: ");
            fgets(questions[i].category, 50, stdin);
            removeNewline(questions[i].category);
            
            printf("Enter new difficulty (1-Easy, 2-Medium, 3-Hard): ");
            scanf("%d", &questions[i].difficulty);
            clearInputBuffer();
            
            printf("\nQuestion updated successfully!\n");
            return;
        }
    }
    printf("\nQuestion ID not found!\n");
}

void removeQuestion(struct Question *questions, int *questionCount) {
    if (*questionCount == 0) {
        printf("\nNo questions to remove.\n");
        return;
    }
    
    int id;
    printf("\nEnter question ID to remove: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    for (int i = 0; i < *questionCount; i++) {
        if (questions[i].id == id) {
            printf("\nRemoving question: %.50s...\n", questions[i].question);
            
            for (int j = i; j < *questionCount - 1; j++) {
                questions[j] = questions[j + 1];
            }
            (*questionCount)--;
            printf("\nQuestion removed successfully!\n");
            return;
        }
    }
    printf("\nQuestion ID not found!\n");
}

void searchQuestions(struct Question *questions, int questionCount) {
    if (questionCount == 0) {
        printf("\nNo questions to search.\n");
        return;
    }
    
    char search[100];
    printf("\nEnter keyword to search in questions or category: ");
    fgets(search, 100, stdin);
    removeNewline(search);
    
    printf("\n--- SEARCH RESULTS ---\n");
    int found = 0;
    
    for (int i = 0; i < questionCount; i++) {
        if (strstr(questions[i].question, search) || strstr(questions[i].category, search)) {
            displayQuestion(questions[i], found + 1);
            printf("Category: %s | Difficulty: %d\n\n", questions[i].category, questions[i].difficulty);
            found++;
        }
    }
    
    if (!found) {
        printf("No matching questions found.\n");
    } else {
        printf("Found %d matching question(s).\n", found);
    }
}

void sortQuestions(struct Question *questions, int questionCount) {
    if (questionCount == 0) {
        printf("\nNo questions to sort.\n");
        return;
    }
    
    printf("\nSort by: 1) Category 2) Difficulty\n");
    printf("Enter choice: ");
    int choice = getChoice();
    
    for (int i = 0; i < questionCount - 1; i++) {
        for (int j = 0; j < questionCount - i - 1; j++) {
            int swap = 0;
            
            switch (choice) {
                case 1: // Sort by category
                    if (strcmp(questions[j].category, questions[j + 1].category) > 0) swap = 1;
                    break;
                case 2: // Sort by difficulty
                    if (questions[j].difficulty > questions[j + 1].difficulty) swap = 1;
                    break;
            }
            
            if (swap) {
                struct Question temp = questions[j];
                questions[j] = questions[j + 1];
                questions[j + 1] = temp;
            }
        }
    }
    
    printf("\nQuestions sorted successfully!\n");
    viewQuestions(questions, questionCount);
}

void viewScores() {
    FILE *file = fopen(SCORES_FILE, "r");
    if (!file) {
        printf("\nNo scores recorded yet.\n");
        return;
    }
    
    printf("\n==========================================\n");
    printf("             HIGH SCORES                 \n");
    printf("==========================================\n");
    printf("Name               | Score | Percentage\n");
    printf("-------------------|-------|------------\n");
    
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    
    fclose(file);
}

void saveQuestions(struct Question *questions, int questionCount) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("\nError saving questions!\n");
        return;
    }
    
    fprintf(file, "%d\n", questionCount);
    for (int i = 0; i < questionCount; i++) {
        fprintf(file, "%d|%s|%s|%s|%s|%s|%d|%s|%d\n", 
                questions[i].id, questions[i].question, 
                questions[i].options[0], questions[i].options[1], 
                questions[i].options[2], questions[i].options[3], 
                questions[i].correctAnswer, questions[i].category, questions[i].difficulty);
    }
    
    fclose(file);
}

int loadQuestions(struct Question *questions) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return 0;
    }
    
    int count;
    fscanf(file, "%d\n", &count);
    
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d|%199[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%d|%49[^|]|%d\n", 
               &questions[i].id, questions[i].question, 
               questions[i].options[0], questions[i].options[1], 
               questions[i].options[2], questions[i].options[3], 
               &questions[i].correctAnswer, questions[i].category, &questions[i].difficulty);
    }
    
    fclose(file);
    return count;
}

void saveScore(struct Player player) {
    FILE *file = fopen(SCORES_FILE, "a");
    if (!file) {
        printf("\nError saving score!\n");
        return;
    }
    
    fprintf(file, "%-18s | %2d/%2d | %5.1f%%\n", 
            player.name, player.score, player.totalQuestions, player.percentage);
    
    fclose(file);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void displayQuestion(struct Question q, int qNum) {
    if (qNum > 0) printf("%d) ", qNum);
    printf("%s\n", q.question);
    for (int i = 0; i < 4; i++) {
        printf("%d) %s\n", i + 1, q.options[i]);
    }
}

void initializeDefaultQuestions(struct Question *questions, int *count) {
    // Question 1
    questions[0].id = 1;
    strcpy(questions[0].question, "What is 2 + 2?");
    strcpy(questions[0].options[0], "3");
    strcpy(questions[0].options[1], "4");
    strcpy(questions[0].options[2], "5");
    strcpy(questions[0].options[3], "6");
    questions[0].correctAnswer = 2;
    strcpy(questions[0].category, "Math");
    questions[0].difficulty = 1;
    
    // Question 2
    questions[1].id = 2;
    strcpy(questions[1].question, "What is the capital of India?");
    strcpy(questions[1].options[0], "Delhi");
    strcpy(questions[1].options[1], "Mumbai");
    strcpy(questions[1].options[2], "Kolkata");
    strcpy(questions[1].options[3], "Chennai");
    questions[1].correctAnswer = 1;
    strcpy(questions[1].category, "Geography");
    questions[1].difficulty = 1;
    
    // Question 3
    questions[2].id = 3;
    strcpy(questions[2].question, "Who wrote 'Romeo and Juliet'?");
    strcpy(questions[2].options[0], "Charles Dickens");
    strcpy(questions[2].options[1], "William Shakespeare");
    strcpy(questions[2].options[2], "Mark Twain");
    strcpy(questions[2].options[3], "Jane Austen");
    questions[2].correctAnswer = 2;
    strcpy(questions[2].category, "Literature");
    questions[2].difficulty = 2;
    
    // Question 4
    questions[3].id = 4;
    strcpy(questions[3].question, "What is the largest planet in our solar system?");
    strcpy(questions[3].options[0], "Earth");
    strcpy(questions[3].options[1], "Mars");
    strcpy(questions[3].options[2], "Jupiter");
    strcpy(questions[3].options[3], "Saturn");
    questions[3].correctAnswer = 3;
    strcpy(questions[3].category, "Science");
    questions[3].difficulty = 2;
    
    // Question 5
    questions[4].id = 5;
    strcpy(questions[4].question, "In which year did World War II end?");
    strcpy(questions[4].options[0], "1944");
    strcpy(questions[4].options[1], "1945");
    strcpy(questions[4].options[2], "1946");
    strcpy(questions[4].options[3], "1947");
    questions[4].correctAnswer = 2;
    strcpy(questions[4].category, "History");
    questions[4].difficulty = 2;
    
    *count = 5;
}

int validateAnswer(int answer) {
    if (answer < 1 || answer > 4) {
        printf("Answer must be between 1 and 4! Try again.\n");
        return 0;
    }
    return 1;
}