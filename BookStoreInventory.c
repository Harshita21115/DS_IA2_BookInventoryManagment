#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 50
#define MAX_GENRE 20
#define LOAN_PERIOD 14  // in days

// Structure to store book information
typedef struct Book {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char genre[MAX_GENRE];
    int stock;
    int reserved;
    int onLoan;
    int sold;
    struct Book* next; // Pointer to the next book in the linked list
} Book;

// Function prototypes
Book* createBook(int id, char* title, char* author, char* genre, int stock);
void addBook(Book** head, int id, char* title, char* author, char* genre, int stock);
void displayBooks(Book* head);
void sellBook(Book* head, int id, int quantity);
void loanBook(Book* head, int id, int quantity);
void returnBook(Book* head, int id, int quantity);
void restockBook(Book* head, int id, int quantity);
void inventoryAnalysis(Book* head);
void freeInventory(Book* head);

int main() {
    Book* inventory = NULL;
    int choice, id, quantity;
    char title[MAX_TITLE], author[MAX_AUTHOR], genre[MAX_GENRE];

    while (1) {
        printf("\n--- Book Inventory Management ---\n");
        printf("1. Display all books\n");
        printf("2. Sell a book\n");
        printf("3. Loan a book\n");
        printf("4. Return a book\n");
        printf("5. Restock a book\n");
        printf("6. Add new book\n");
        printf("7. Inventory analysis\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBooks(inventory);
                break;
            case 2:
                printf("Enter Book ID to sell: ");
                scanf("%d", &id);
                printf("Enter quantity to sell: ");
                scanf("%d", &quantity);
                sellBook(inventory, id, quantity);
                break;
            case 3:
                printf("Enter Book ID to loan: ");
                scanf("%d", &id);
                printf("Enter quantity to loan: ");
                scanf("%d", &quantity);
                loanBook(inventory, id, quantity);
                break;
            case 4:
                printf("Enter Book ID to return: ");
                scanf("%d", &id);
                printf("Enter quantity to return: ");
                scanf("%d", &quantity);
                returnBook(inventory, id, quantity);
                break;
            case 5:
                printf("Enter Book ID to restock: ");
                scanf("%d", &id);
                printf("Enter quantity to restock: ");
                scanf("%d", &quantity);
                restockBook(inventory, id, quantity);
                break;
            case 6:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                printf("Enter Book Title: ");
                getchar();
                fgets(title, MAX_TITLE, stdin);
                title[strcspn(title, "\n")] = '\0';
                printf("Enter Author: ");
                fgets(author, MAX_AUTHOR, stdin);
                author[strcspn(author, "\n")] = '\0';
                printf("Enter Genre: ");
                fgets(genre, MAX_GENRE, stdin);
                genre[strcspn(genre, "\n")] = '\0';
                printf("Enter Stock: ");
                scanf("%d", &quantity);
                addBook(&inventory, id, title, author, genre, quantity);
                break;
            case 7:
                inventoryAnalysis(inventory);
                break;
            case 8:
                printf("Exiting program.\n");
                freeInventory(inventory); // Free memory before exit
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to create a new book
Book* createBook(int id, char* title, char* author, char* genre, int stock) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    strcpy(newBook->genre, genre);
    newBook->stock = stock;
    newBook->reserved = 0;
    newBook->onLoan = 0;
    newBook->sold = 0;
    newBook->next = NULL;
    return newBook;
}

// Function to add a new book to the inventory
void addBook(Book** head, int id, char* title, char* author, char* genre, int stock) {
    Book* newBook = createBook(id, title, author, genre, stock);
    newBook->next = *head; // Insert at the beginning
    *head = newBook;
    printf("Book '%s' added to inventory.\n", title);
}

// Function to display all books in the inventory
void displayBooks(Book* head) {
    printf("\n--- Book Inventory ---\n");
    while (head) {
        printf("ID: %d | Title: %s | Author: %s | Genre: %s | Stock: %d | Reserved: %d | On Loan: %d | Sold: %d\n",
               head->id, head->title, head->author, head->genre,
               head->stock, head->reserved, head->onLoan, head->sold);
        head = head->next;
    }
}

// Function to sell a book
void sellBook(Book* head, int id, int quantity) {
    while (head) {
        if (head->id == id) {
            if (head->stock >= quantity) {
                head->stock -= quantity;
                head->sold += quantity;
                printf("Sold %d of '%s'. Remaining stock: %d\n", quantity, head->title, head->stock);
                return;
            } else {
                printf("Not enough stock to sell.\n");
                return;
            }
        }
        head = head->next;
    }
    printf("Book not found.\n");
}

// Function to loan a book
void loanBook(Book* head, int id, int quantity) {
    while (head) {
        if (head->id == id) {
            if (head->stock >= quantity) {
                head->stock -= quantity;
                head->onLoan += quantity;
                printf("Loaned %d of '%s'. Remaining stock: %d\n", quantity, head->title, head->stock);
                return;
            } else {
                printf("Not enough stock to loan.\n");
                return;
            }
        }
        head = head->next;
    }
    printf("Book not found.\n");
}

// Function to return a book
void returnBook(Book* head, int id, int quantity) {
    while (head) {
        if (head->id == id) {
            if (head->onLoan >= quantity) {
                head->stock += quantity;
                head->onLoan -= quantity;
                printf("Returned %d of '%s'. Updated stock: %d\n", quantity, head->title, head->stock);
                return;
            } else {
                printf("Error: Returning more than loaned.\n");
                return;
            }
        }
        head = head->next;
    }
    printf("Book not found.\n");
}

// Function to restock a book
void restockBook(Book* head, int id, int quantity) {
    while (head) {
        if (head->id == id) {
            head->stock += quantity;
            printf("Restocked %d of '%s'. Total stock: %d\n", quantity, head->title, head->stock);
            return;
        }
        head = head->next;
    }
    printf("Book not found.\n");
}

// Function for basic inventory analysis
void inventoryAnalysis(Book* head) {
    printf("\n--- Inventory Analysis ---\n");
    while (head) {
        printf("Title: %s | Sold: %d | On Loan: %d | In Stock: %d\n",
               head->title, head->sold, head->onLoan, head->stock);
        head = head->next;
    }
}

// Function to free the inventory memory
void freeInventory(Book* head) {
    Book* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}