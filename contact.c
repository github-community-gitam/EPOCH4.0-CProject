
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define FILE_NAME "contacts.txt"

struct Contact {
    char name[50];
    char phone[20];
};

/* Function declarations */
void loadContacts(struct Contact list[], int *count);
void saveContacts(struct Contact list[], int count);
void addContact(struct Contact list[], int *count);
void viewContacts(struct Contact list[], int count);
void deleteContact(struct Contact list[], int *count);
int isValidPhone(char phone[]);

int main() {
    struct Contact list[MAX];
    int count = 0, choice;

    loadContacts(list, &count);

    while (1) {
        printf("\n--- CONTACT BOOK ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Delete Contact\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addContact(list, &count);
                break;
            case 2:
                viewContacts(list, count);
                break;
            case 3:
                deleteContact(list, &count);
                break;
            case 4:
                saveContacts(list, count);
                printf("Contacts saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}

/* Load contacts from file */
void loadContacts(struct Contact list[], int *count) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%49[^,],%19[^\n]\n",
                  list[*count].name,
                  list[*count].phone) == 2) {
        (*count)++;
        if (*count >= MAX) break;
    }
    fclose(fp);
}

/* Save contacts to file */
void saveContacts(struct Contact list[], int count) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (!fp) {
        printf("Error saving file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s\n", list[i].name, list[i].phone);
    }
    fclose(fp);
}

/* Validate 10-digit phone number */
int isValidPhone(char phone[]) {
    if (strlen(phone) != 10)
        return 0;

    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i]))
            return 0;
    }
    return 1;
}

/* Add contact */
void addContact(struct Contact list[], int *count) {
    if (*count >= MAX) {
        printf("Contact list full.\n");
        return;
    }

    getchar();  // clear newline

    printf("Enter name: ");
    fgets(list[*count].name, 50, stdin);
    list[*count].name[strcspn(list[*count].name, "\n")] = '\0';

    while (1) {
        printf("Enter 10-digit phone number: ");
        fgets(list[*count].phone, 20, stdin);
        list[*count].phone[strcspn(list[*count].phone, "\n")] = '\0';

        if (isValidPhone(list[*count].phone))
            break;

        printf("Invalid phone number. Try again.\n");
    }

    (*count)++;
    printf("Contact added successfully.\n");
}

/* View contacts */
void viewContacts(struct Contact list[], int count) {
    if (count == 0) {
        printf("No contacts available.\n");
        return;
    }

    printf("\n--- SAVED CONTACTS ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %s\n", i + 1, list[i].name, list[i].phone);
    }
}

/* Delete contact */
void deleteContact(struct Contact list[], int *count) {
    int index;

    if (*count == 0) {
        printf("No contacts to delete.\n");
        return;
    }

    viewContacts(list, *count);

    printf("Enter contact number to delete: ");
    if (scanf("%d", &index) != 1 || index < 1 || index > *count) {
        printf("Invalid choice.\n");
        while (getchar() != '\n');
        return;
    }

    for (int i = index - 1; i < *count - 1; i++) {
        list[i] = list[i + 1];
    }

    (*count)--;
    printf("Contact deleted successfully.\n");
}

