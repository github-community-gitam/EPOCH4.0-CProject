#include <stdio.h>
#include <string.h>

#define MAX_EXPENSES 20
#define FILE_NAME "expenses.txt"

/* Structure to store expense details */
struct Expense {
    char name[50];   // Name of the expense
    float amount;    // Amount spent
};

/* Function prototypes */
void loadFromFile(struct Expense exp[], int *count, float *total);
void saveToFile(struct Expense exp[], int count);
void addExpense(struct Expense exp[], int *count, float *total);
void viewExpenses(struct Expense exp[], int count);
void viewTotal(float total);

int main() {
    struct Expense exp[MAX_EXPENSES];
    int count = 0;
    float total = 0.0;
    int choice;

    /* Load existing expenses from file */
    loadFromFile(exp, &count, &total);

    while (1) {
        printf("\n--- EXPENSE TRACKER ---\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. View Total\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                addExpense(exp, &count, &total);
                saveToFile(exp, count);
                break;

            case 2:
                viewExpenses(exp, count);
                break;

            case 3:
                viewTotal(total);
                break;

            case 4:
                printf("Exiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please select between 1 and 4.\n");
        }
    }
}

/* Load expenses from file */
void loadFromFile(struct Expense exp[], int *count, float *total) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        // File does not exist, start fresh
        return;
    }

    while (*count < MAX_EXPENSES &&
           fscanf(fp, "%49[^,],%f\n", exp[*count].name, &exp[*count].amount) == 2) {
        *total += exp[*count].amount;
        (*count)++;
    }

    fclose(fp);
}

/* Save expenses to file */
void saveToFile(struct Expense exp[], int count) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error saving data to file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%.2f\n", exp[i].name, exp[i].amount);
    }

    fclose(fp);
}

/* Add a new expense */
void addExpense(struct Expense exp[], int *count, float *total) {
    if (*count >= MAX_EXPENSES) {
        printf("Expense limit reached.\n");
        return;
    }

    printf("Enter expense name: ");
    getchar(); // consume leftover newline
    fgets(exp[*count].name, sizeof(exp[*count].name), stdin);
    exp[*count].name[strcspn(exp[*count].name, "\n")] = '\0'; // remove newline

    printf("Enter amount: ");
    if (scanf("%f", &exp[*count].amount) != 1 || exp[*count].amount <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        while (getchar() != '\n');
        return;
    }

    *total += exp[*count].amount;
    (*count)++;

    printf("Expense added successfully.\n");
}

/* Display all expenses */
void viewExpenses(struct Expense exp[], int count) {
    if (count == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("\n%-20s | %10s\n", "Expense", "Amount");
    printf("--------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-20s | %10.2f\n", exp[i].name, exp[i].amount);
    }
}

/* Display total expense */
void viewTotal(float total) {
    printf("Total Expense: %.2f\n", total);
}
#include <stdio.h>
#include <string.h>

#define MAX_EXPENSES 20
#define FILE_NAME "expenses.txt"

/* Structure to store expense details */
struct Expense {
    char name[50];   // Name of the expense
    float amount;    // Amount spent
};

/* Function prototypes */
void loadFromFile(struct Expense exp[], int *count, float *total);
void saveToFile(struct Expense exp[], int count);
void addExpense(struct Expense exp[], int *count, float *total);
void viewExpenses(struct Expense exp[], int count);
void viewTotal(float total);

int main() {
    struct Expense exp[MAX_EXPENSES];
    int count = 0;
    float total = 0.0;
    int choice;

    /* Load existing expenses from file */
    loadFromFile(exp, &count, &total);

    while (1) {
        printf("\n--- EXPENSE TRACKER ---\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. View Total\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                addExpense(exp, &count, &total);
                saveToFile(exp, count);
                break;

            case 2:
                viewExpenses(exp, count);
                break;

            case 3:
                viewTotal(total);
                break;

            case 4:
                printf("Exiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please select between 1 and 4.\n");
        }
    }
}

/* Load expenses from file */
void loadFromFile(struct Expense exp[], int *count, float *total) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        // File does not exist, start fresh
        return;
    }

    while (*count < MAX_EXPENSES &&
           fscanf(fp, "%49[^,],%f\n", exp[*count].name, &exp[*count].amount) == 2) {
        *total += exp[*count].amount;
        (*count)++;
    }

    fclose(fp);
}

/* Save expenses to file */
void saveToFile(struct Expense exp[], int count) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error saving data to file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%.2f\n", exp[i].name, exp[i].amount);
    }

    fclose(fp);
}

/* Add a new expense */
void addExpense(struct Expense exp[], int *count, float *total) {
    if (*count >= MAX_EXPENSES) {
        printf("Expense limit reached.\n");
        return;
    }

    printf("Enter expense name: ");
    getchar(); // consume leftover newline
    fgets(exp[*count].name, sizeof(exp[*count].name), stdin);
    exp[*count].name[strcspn(exp[*count].name, "\n")] = '\0'; // remove newline

    printf("Enter amount: ");
    if (scanf("%f", &exp[*count].amount) != 1 || exp[*count].amount <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        while (getchar() != '\n');
        return;
    }

    *total += exp[*count].amount;
    (*count)++;

    printf("Expense added successfully.\n");
}

/* Display all expenses */
void viewExpenses(struct Expense exp[], int count) {
    if (count == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("\n%-20s | %10s\n", "Expense", "Amount");
    printf("--------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-20s | %10.2f\n", exp[i].name, exp[i].amount);
    }
}

/* Display total expense */
void viewTotal(float total) {
    printf("Total Expense: %.2f\n", total);
}

