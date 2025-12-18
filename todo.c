#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 50
#define MAX_DESC 200

typedef struct {
    char description[MAX_DESC];
    char priority[10];
    char category[30];
    int completed;
} Task;

Task tasks[MAX_TASKS];
int count = 0;

void loadTasks() {
    FILE *file = fopen("tasks.dat", "rb");
    if (file) {
        fread(&count, sizeof(int), 1, file);
        fread(tasks, sizeof(Task), count, file);
        fclose(file);
    }
}

void saveTasks() {
    FILE *file = fopen("tasks.dat", "wb");
    if (file) {
        fwrite(&count, sizeof(int), 1, file);
        fwrite(tasks, sizeof(Task), count, file);
        fclose(file);
    }
}

void addTask() {
    if (count >= MAX_TASKS) {
        printf("Task limit reached!\n");
        return;
    }
    printf("Enter task description: ");
    getchar();
    fgets(tasks[count].description, MAX_DESC, stdin);
    tasks[count].description[strcspn(tasks[count].description, "\n")] = 0;
    
    printf("Enter priority (High/Medium/Low): ");
    fgets(tasks[count].priority, 10, stdin);
    tasks[count].priority[strcspn(tasks[count].priority, "\n")] = 0;
    
    printf("Enter category: ");
    fgets(tasks[count].category, 30, stdin);
    tasks[count].category[strcspn(tasks[count].category, "\n")] = 0;
    
    tasks[count].completed = 0;
    count++;
    printf("Task added successfully!\n");
}

void viewTasks() {
    if (count == 0) {
        printf("No tasks available.\n");
        return;
    }
    printf("\n%-3s %-30s %-10s %-15s %-10s\n", "#", "Description", "Priority", "Category", "Status");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-3d %-30s %-10s %-15s %-10s\n", i + 1, tasks[i].description, 
               tasks[i].priority, tasks[i].category, 
               tasks[i].completed ? "Done" : "Pending");
    }
}

void editTask() {
    int id;
    printf("Enter task number to edit: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > count) {
        printf("Invalid task number!\n");
        return;
    }
    id--;
    printf("Current: %s\n", tasks[id].description);
    printf("New description: ");
    getchar();
    fgets(tasks[id].description, MAX_DESC, stdin);
    tasks[id].description[strcspn(tasks[id].description, "\n")] = 0;
    printf("Task updated!\n");
}

void removeTask() {
    int id;
    printf("Enter task number to remove: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > count) {
        printf("Invalid task number!\n");
        return;
    }
    id--;
    for (int i = id; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    count--;
    printf("Task removed!\n");
}

void markComplete() {
    int id;
    printf("Enter task number to mark complete: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > count) {
        printf("Invalid task number!\n");
        return;
    }
    tasks[id - 1].completed = 1;
    printf("Task marked as complete!\n");
}

void sortTasks() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(tasks[j].priority, tasks[j + 1].priority) > 0) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
    printf("Tasks sorted by priority!\n");
}

void searchTasks() {
    char keyword[50];
    printf("Enter search keyword: ");
    getchar();
    fgets(keyword, 50, stdin);
    keyword[strcspn(keyword, "\n")] = 0;
    
    printf("\nSearch Results:\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(tasks[i].description, keyword) || strstr(tasks[i].category, keyword)) {
            printf("%d. %s [%s] (%s)\n", i + 1, tasks[i].description, 
                   tasks[i].priority, tasks[i].category);
            found = 1;
        }
    }
    if (!found) printf("No matching tasks found.\n");
}

int main() {
    loadTasks();
    int choice;

    while (1) {
        printf("\n=== ENHANCED TO-DO LIST ===\n");
        printf("1. Add Task\n");
        printf("2. View All Tasks\n");
        printf("3. Edit Task\n");
        printf("4. Remove Task\n");
        printf("5. Mark Complete\n");
        printf("6. Sort by Priority\n");
        printf("7. Search Tasks\n");
        printf("8. Save & Exit\n");
        printf("Enter choice (1-8): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Please enter a valid number!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: editTask(); break;
            case 4: removeTask(); break;
            case 5: markComplete(); break;
            case 6: sortTasks(); break;
            case 7: searchTasks(); break;
            case 8: saveTasks(); printf("Tasks saved. Goodbye!\n"); return 0;
            default: printf("Invalid choice! Please enter 1-8.\n");
        }
    }
}
