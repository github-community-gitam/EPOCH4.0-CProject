#include <stdio.h>
#include <string.h>

#define MAX 20
#define FILE_NAME "students.txt"

struct Student {
    char name[50];
    int roll;
};

/* Function declarations */
void loadStudents(struct Student s[], int *count);
void saveStudents(struct Student s[], int count);
void addStudent(struct Student s[], int *count);
void viewStudents(struct Student s[], int count);

int main() {
    struct Student s[MAX];
    int count = 0;
    int choice;

    /* Load existing students from file */
    loadStudents(s, &count);

    while (1) {
        printf("\n--- STUDENT MANAGEMENT SYSTEM ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(s, &count);
                break;
            case 2:
                viewStudents(s, count);
                break;
            case 3:
                saveStudents(s, count);
                printf("Student data saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

/* Load students from file */
void loadStudents(struct Student s[], int *count) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%49[^,],%d\n", s[*count].name, &s[*count].roll) == 2) {
        (*count)++;
        if (*count >= MAX) break;
    }

    fclose(fp);
}

/* Save students to file */
void saveStudents(struct Student s[], int count) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error saving student data.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%d\n", s[i].name, s[i].roll);
    }

    fclose(fp);
}

/* Add a new student */
void addStudent(struct Student s[], int *count) {
    if (*count >= MAX) {
        printf("Student list is full.\n");
        return;
    }

    printf("Enter name: ");
    getchar();
    fgets(s[*count].name, 50, stdin);
    s[*count].name[strcspn(s[*count].name, "\n")] = '\0';

    printf("Enter roll number: ");
    if (scanf("%d", &s[*count].roll) != 1) {
        printf("Invalid roll number.\n");
        while (getchar() != '\n');
        return;
    }

    (*count)++;
    printf("Student added successfully.\n");
}

/* View all students */
void viewStudents(struct Student s[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\n--- STUDENT LIST ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - Roll %d\n", i + 1, s[i].name, s[i].roll);
    }
}

