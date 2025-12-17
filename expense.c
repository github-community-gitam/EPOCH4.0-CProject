#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define MAX_NAME 50
#define MAX_CATEGORY 30
#define FILENAME "expenses.txt"

struct Expense {
    int id;
    char name[MAX_NAME];
    char category[MAX_CATEGORY];
    float amount;
    char date[11]; // DD/MM/YYYY
};

// Function prototypes
void displayMenu();
int getChoice();
void addExpense(struct Expense *exp, int *count);
void viewExpenses(struct Expense *exp, int count);
void editExpense(struct Expense *exp, int count);
void removeExpense(struct Expense *exp, int *count);
void searchExpense(struct Expense *exp, int count);
void sortExpenses(struct Expense *exp, int count);
float calculateTotal(struct Expense *exp, int count);
void saveToFile(struct Expense *exp, int count);
int loadFromFile(struct Expense *exp);
void clearInputBuffer();
int validateAmount(float amount);
void removeNewline(char *str);

int main() {
    struct Expense expenses[MAX_EXPENSES];
    int count = 0;
    int choice;

    // Load existing data
    count = loadFromFile(expenses);
    printf("\n=== EXPENSE TRACKER ===\n");
    printf("Loaded %d existing expenses.\n", count);

    while (1) {
        displayMenu();
        choice = getChoice();

        switch (choice) {
            case 1:
                addExpense(expenses, &count);
                break;
            case 2:
                viewExpenses(expenses, count);
                break;
            case 3:
                editExpense(expenses, count);
                break;
            case 4:
                removeExpense(expenses, &count);
                break;
            case 5:
                searchExpense(expenses, count);
                break;
            case 6:
                sortExpenses(expenses, count);
                break;
            case 7:
                printf("\n💰 Total Expenses: $%.2f\n", calculateTotal(expenses, count));
                break;
            case 8:
                saveToFile(expenses, count);
                printf("\n✅ Data saved successfully!\n");
                break;
            case 9:
                saveToFile(expenses, count);
                printf("\n👋 Goodbye! Data saved automatically.\n");
                return 0;
            default:
                printf("\n❌ Invalid choice! Please try again.\n");
        }
    }
}

void displayMenu() {
    printf("\n==========================================\n");
    printf("           EXPENSE TRACKER MENU          \n");
    printf("==========================================\n");
    printf("1. 📝 Add New Expense\n");
    printf("2. 📋 View All Expenses\n");
    printf("3. ✏️  Edit Expense\n");
    printf("4. 🗑️  Remove Expense\n");
    printf("5. 🔍 Search Expenses\n");
    printf("6. 📊 Sort Expenses\n");
    printf("7. 💰 View Total\n");
    printf("8. 💾 Save Data\n");
    printf("9. 🚪 Exit\n");
    printf("==========================================\n");
    printf("Enter your choice (1-9): ");
}

int getChoice() {
    int choice;
    while (scanf("%d", &choice) != 1) {
        printf("❌ Invalid input! Please enter a number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return choice;
}

void addExpense(struct Expense *exp, int *count) {
    if (*count >= MAX_EXPENSES) {
        printf("\n❌ Maximum expense limit reached!\n");
        return;
    }

    struct Expense newExp;
    newExp.id = *count + 1;

    printf("\n--- ADD NEW EXPENSE ---\n");
    
    printf("Enter expense name: ");
    fgets(newExp.name, MAX_NAME, stdin);
    removeNewline(newExp.name);
    
    printf("Enter category: ");
    fgets(newExp.category, MAX_CATEGORY, stdin);
    removeNewline(newExp.category);
    
    do {
        printf("Enter amount ($): ");
        scanf("%f", &newExp.amount);
        clearInputBuffer();
    } while (!validateAmount(newExp.amount));
    
    printf("Enter date (DD/MM/YYYY): ");
    fgets(newExp.date, 11, stdin);
    removeNewline(newExp.date);
    
    exp[*count] = newExp;
    (*count)++;
    
    printf("\n✅ Expense added successfully!\n");
}

void viewExpenses(struct Expense *exp, int count) {
    if (count == 0) {
        printf("\n📭 No expenses recorded yet.\n");
        return;
    }
    
    printf("\n==========================================\n");
    printf("              ALL EXPENSES               \n");
    printf("==========================================\n");
    printf("ID | Name                | Category     | Amount   | Date\n");
    printf("---|---------------------|--------------|----------|----------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-2d | %-19s | %-12s | $%-7.2f | %s\n", 
               exp[i].id, exp[i].name, exp[i].category, exp[i].amount, exp[i].date);
    }
    printf("==========================================\n");
    printf("Total: $%.2f\n", calculateTotal(exp, count));
}

void editExpense(struct Expense *exp, int count) {
    if (count == 0) {
        printf("\n📭 No expenses to edit.\n");
        return;
    }
    
    int id;
    printf("\nEnter expense ID to edit: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    for (int i = 0; i < count; i++) {
        if (exp[i].id == id) {
            printf("\n--- EDITING EXPENSE ID %d ---\n", id);
            printf("Current: %s | %s | $%.2f | %s\n", 
                   exp[i].name, exp[i].category, exp[i].amount, exp[i].date);
            
            printf("\nEnter new name: ");
            fgets(exp[i].name, MAX_NAME, stdin);
            removeNewline(exp[i].name);
            
            printf("Enter new category: ");
            fgets(exp[i].category, MAX_CATEGORY, stdin);
            removeNewline(exp[i].category);
            
            do {
                printf("Enter new amount ($): ");
                scanf("%f", &exp[i].amount);
                clearInputBuffer();
            } while (!validateAmount(exp[i].amount));
            
            printf("Enter new date (DD/MM/YYYY): ");
            fgets(exp[i].date, 11, stdin);
            removeNewline(exp[i].date);
            
            printf("\n✅ Expense updated successfully!\n");
            return;
        }
    }
    printf("\n❌ Expense ID not found!\n");
}

void removeExpense(struct Expense *exp, int *count) {
    if (*count == 0) {
        printf("\n📭 No expenses to remove.\n");
        return;
    }
    
    int id;
    printf("\nEnter expense ID to remove: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    for (int i = 0; i < *count; i++) {
        if (exp[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                exp[j] = exp[j + 1];
            }
            (*count)--;
            printf("\n✅ Expense removed successfully!\n");
            return;
        }
    }
    printf("\n❌ Expense ID not found!\n");
}

void searchExpense(struct Expense *exp, int count) {
    if (count == 0) {
        printf("\n📭 No expenses to search.\n");
        return;
    }
    
    char search[MAX_NAME];
    printf("\nEnter name or category to search: ");
    fgets(search, MAX_NAME, stdin);
    removeNewline(search);
    
    printf("\n--- SEARCH RESULTS ---\n");
    int found = 0;
    
    for (int i = 0; i < count; i++) {
        if (strstr(exp[i].name, search) || strstr(exp[i].category, search)) {
            printf("ID %d: %s | %s | $%.2f | %s\n", 
                   exp[i].id, exp[i].name, exp[i].category, exp[i].amount, exp[i].date);
            found++;
        }
    }
    
    if (!found) {
        printf("❌ No matching expenses found.\n");
    } else {
        printf("\n✅ Found %d matching expense(s).\n", found);
    }
}

void sortExpenses(struct Expense *exp, int count) {
    if (count == 0) {
        printf("\n📭 No expenses to sort.\n");
        return;
    }
    
    printf("\nSort by: 1) Amount 2) Name 3) Category\n");
    printf("Enter choice: ");
    int choice = getChoice();
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int swap = 0;
            
            switch (choice) {
                case 1: // Sort by amount
                    if (exp[j].amount > exp[j + 1].amount) swap = 1;
                    break;
                case 2: // Sort by name
                    if (strcmp(exp[j].name, exp[j + 1].name) > 0) swap = 1;
                    break;
                case 3: // Sort by category
                    if (strcmp(exp[j].category, exp[j + 1].category) > 0) swap = 1;
                    break;
            }
            
            if (swap) {
                struct Expense temp = exp[j];
                exp[j] = exp[j + 1];
                exp[j + 1] = temp;
            }
        }
    }
    
    printf("\n✅ Expenses sorted successfully!\n");
    viewExpenses(exp, count);
}

float calculateTotal(struct Expense *exp, int count) {
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += exp[i].amount;
    }
    return total;
}

void saveToFile(struct Expense *exp, int count) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("\n❌ Error saving to file!\n");
        return;
    }
    
    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%.2f|%s\n", 
                exp[i].id, exp[i].name, exp[i].category, exp[i].amount, exp[i].date);
    }
    
    fclose(file);
}

int loadFromFile(struct Expense *exp) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return 0; // No file exists yet
    }
    
    int count;
    fscanf(file, "%d\n", &count);
    
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d|%49[^|]|%29[^|]|%f|%10[^\n]\n", 
               &exp[i].id, exp[i].name, exp[i].category, &exp[i].amount, exp[i].date);
    }
    
    fclose(file);
    return count;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validateAmount(float amount) {
    if (amount <= 0) {
        printf("❌ Amount must be positive! Try again.\n");
        return 0;
    }
    return 1;
}

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}
