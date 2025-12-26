#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_NAME 50
#define MAX_PHONE 20
#define MAX_EMAIL 50
#define MAX_ADDRESS 100
#define FILENAME "contacts.txt"

struct Contact {
    int id;
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
    char address[MAX_ADDRESS];
    char category[30]; // Family, Work, Friend
};

// Function prototypes
void displayMenu();
int getChoice();
void addContact(struct Contact *contacts, int *count);
void viewContacts(struct Contact *contacts, int count);
void editContact(struct Contact *contacts, int count);
void removeContact(struct Contact *contacts, int *count);
void searchContact(struct Contact *contacts, int count);
void sortContacts(struct Contact *contacts, int count);
void saveToFile(struct Contact *contacts, int count);
int loadFromFile(struct Contact *contacts);
void clearInputBuffer();
void removeNewline(char *str);
void displayContactDetails(struct Contact contact);
int validatePhone(char *phone);

int main() {
    struct Contact contacts[MAX_CONTACTS];
    int count = 0;
    int choice;

    // Load existing data
    count = loadFromFile(contacts);
    printf("\n=== CONTACT BOOK ===\n");
    printf("Loaded %d existing contacts.\n", count);

    while (1) {
        displayMenu();
        choice = getChoice();

        switch (choice) {
            case 1:
                addContact(contacts, &count);
                break;
            case 2:
                viewContacts(contacts, count);
                break;
            case 3:
                editContact(contacts, count);
                break;
            case 4:
                removeContact(contacts, &count);
                break;
            case 5:
                searchContact(contacts, count);
                break;
            case 6:
                sortContacts(contacts, count);
                break;
            case 7:
                saveToFile(contacts, count);
                printf("\nData saved successfully!\n");
                break;
            case 8:
                saveToFile(contacts, count);
                printf("\nGoodbye! Data saved automatically.\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void displayMenu() {
    printf("\n==========================================\n");
    printf("             CONTACT BOOK                \n");
    printf("==========================================\n");
    printf("1. Add New Contact\n");
    printf("2. View All Contacts\n");
    printf("3. Edit Contact\n");
    printf("4. Remove Contact\n");
    printf("5. Search Contacts\n");
    printf("6. Sort Contacts\n");
    printf("7. Save Data\n");
    printf("8. Exit\n");
    printf("==========================================\n");
    printf("Enter your choice (1-8): ");
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

void addContact(struct Contact *contacts, int *count) {
    if (*count >= MAX_CONTACTS) {
        printf("\nMaximum contact limit reached!\n");
        return;
    }

    struct Contact newContact;
    newContact.id = *count + 1;

    printf("\n--- ADD NEW CONTACT ---\n");
    
    printf("Enter name: ");
    fgets(newContact.name, MAX_NAME, stdin);
    removeNewline(newContact.name);
    
    do {
        printf("Enter phone number: ");
        fgets(newContact.phone, MAX_PHONE, stdin);
        removeNewline(newContact.phone);
    } while (!validatePhone(newContact.phone));
    
    printf("Enter email: ");
    fgets(newContact.email, MAX_EMAIL, stdin);
    removeNewline(newContact.email);
    
    printf("Enter address: ");
    fgets(newContact.address, MAX_ADDRESS, stdin);
    removeNewline(newContact.address);
    
    printf("Enter category (Family/Work/Friend): ");
    fgets(newContact.category, 30, stdin);
    removeNewline(newContact.category);
    
    contacts[*count] = newContact;
    (*count)++;
    
    printf("\nContact added successfully!\n");
}

void viewContacts(struct Contact *contacts, int count) {
    if (count == 0) {
        printf("\nNo contacts saved yet.\n");
        return;
    }
    
    printf("\n==========================================\n");
    printf("              ALL CONTACTS               \n");
    printf("==========================================\n");
    printf("ID | Name               | Phone        | Category\n");
    printf("---|--------------------|--------------|-----------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-2d | %-18s | %-12s | %s\n", 
               contacts[i].id, contacts[i].name, contacts[i].phone, contacts[i].category);
    }
    printf("==========================================\n");
    printf("Total Contacts: %d\n", count);
}

void editContact(struct Contact *contacts, int count) {
    if (count == 0) {
        printf("\nNo contacts to edit.\n");
        return;
    }
    
    int id;
    printf("\nEnter contact ID to edit: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    for (int i = 0; i < count; i++) {
        if (contacts[i].id == id) {
            printf("\n--- EDITING CONTACT ID %d ---\n", id);
            displayContactDetails(contacts[i]);
            
            printf("\nEnter new name: ");
            fgets(contacts[i].name, MAX_NAME, stdin);
            removeNewline(contacts[i].name);
            
            do {
                printf("Enter new phone: ");
                fgets(contacts[i].phone, MAX_PHONE, stdin);
                removeNewline(contacts[i].phone);
            } while (!validatePhone(contacts[i].phone));
            
            printf("Enter new email: ");
            fgets(contacts[i].email, MAX_EMAIL, stdin);
            removeNewline(contacts[i].email);
            
            printf("Enter new address: ");
            fgets(contacts[i].address, MAX_ADDRESS, stdin);
            removeNewline(contacts[i].address);
            
            printf("Enter new category: ");
            fgets(contacts[i].category, 30, stdin);
            removeNewline(contacts[i].category);
            
            printf("\nContact updated successfully!\n");
            return;
        }
    }
    printf("\nContact ID not found!\n");
}

void removeContact(struct Contact *contacts, int *count) {
    if (*count == 0) {
        printf("\nNo contacts to remove.\n");
        return;
    }
    
    int id;
    printf("\nEnter contact ID to remove: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    for (int i = 0; i < *count; i++) {
        if (contacts[i].id == id) {
            printf("\nRemoving: %s (%s)\n", contacts[i].name, contacts[i].phone);
            
            for (int j = i; j < *count - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            (*count)--;
            printf("\nContact removed successfully!\n");
            return;
        }
    }
    printf("\nContact ID not found!\n");
}

void searchContact(struct Contact *contacts, int count) {
    if (count == 0) {
        printf("\nNo contacts to search.\n");
        return;
    }
    
    char search[MAX_NAME];
    printf("\nEnter name, phone, or category to search: ");
    fgets(search, MAX_NAME, stdin);
    removeNewline(search);
    
    printf("\n--- SEARCH RESULTS ---\n");
    int found = 0;
    
    for (int i = 0; i < count; i++) {
        if (strstr(contacts[i].name, search) || strstr(contacts[i].phone, search) || 
            strstr(contacts[i].category, search)) {
            displayContactDetails(contacts[i]);
            printf("\n");
            found++;
        }
    }
    
    if (!found) {
        printf("No matching contacts found.\n");
    } else {
        printf("Found %d matching contact(s).\n", found);
    }
}

void sortContacts(struct Contact *contacts, int count) {
    if (count == 0) {
        printf("\nNo contacts to sort.\n");
        return;
    }
    
    printf("\nSort by: 1) Name 2) Phone 3) Category\n");
    printf("Enter choice: ");
    int choice = getChoice();
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int swap = 0;
            
            switch (choice) {
                case 1: // Sort by name
                    if (strcmp(contacts[j].name, contacts[j + 1].name) > 0) swap = 1;
                    break;
                case 2: // Sort by phone
                    if (strcmp(contacts[j].phone, contacts[j + 1].phone) > 0) swap = 1;
                    break;
                case 3: // Sort by category
                    if (strcmp(contacts[j].category, contacts[j + 1].category) > 0) swap = 1;
                    break;
            }
            
            if (swap) {
                struct Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
    
    printf("\nContacts sorted successfully!\n");
    viewContacts(contacts, count);
}

void saveToFile(struct Contact *contacts, int count) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("\nError saving to file!\n");
        return;
    }
    
    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%s|%s|%s\n", 
                contacts[i].id, contacts[i].name, contacts[i].phone, 
                contacts[i].email, contacts[i].address, contacts[i].category);
    }
    
    fclose(file);
}

int loadFromFile(struct Contact *contacts) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return 0; // No file exists yet
    }
    
    int count;
    fscanf(file, "%d\n", &count);
    
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d|%49[^|]|%19[^|]|%49[^|]|%99[^|]|%29[^\n]\n", 
               &contacts[i].id, contacts[i].name, contacts[i].phone, 
               contacts[i].email, contacts[i].address, contacts[i].category);
    }
    
    fclose(file);
    return count;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void displayContactDetails(struct Contact contact) {
    printf("ID: %d | Name: %s | Phone: %s | Email: %s | Address: %s | Category: %s", 
           contact.id, contact.name, contact.phone, contact.email, 
           contact.address, contact.category);
}

int validatePhone(char *phone) {
    if (strlen(phone) < 10) {
        printf("Phone number must be at least 10 digits! Try again.\n");
        return 0;
    }
    return 1;
}