#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_NAME_LENGTH 100


struct Book {
	
	char title[MAX_TITLE_LENGTH];
	char author[MAX_AUTHOR_LENGTH];
	int id;
	int is_available;
	
};


struct User {
	
	char name[MAX_NAME_LENGTH];
	int id;
};


struct Book library[MAX_BOOKS];
struct User users[MAX_USERS];
int num_books = 0;
int num_users = 0;


void addUser() {
	
	if (num_users < MAX_USERS) {
		struct User new_user;
		printf("Enter your name: ");
		fgets(new_user.name, MAX_NAME_LENGTH, stdin);
		new_user.name[strcspn(new_user.name, "\n")] = 0;
		new_user.id = num_users + 1;
		users[num_users++] = new_user;
		printf("User added!\n");
	}
	else {
		printf("Maximum number of users reached!\n");
	}
}


void displayUsers() {
	
	if (num_users == 0) {
		printf("No users in the system.\n");
	}
	else {
		printf("User List:\n");
		printf("%-5s %-20s\n", "ID", "Name");
		for (int i = 0; i < num_users; i++) {
			printf("%-5d %-20s\n", users[i].id, users[i].name);
		}	
	}	
}


void addBook() {
	
	if (num_books < MAX_BOOKS) {
		struct Book new_book;
		printf("Enter book title: ");
		fgets(new_book.title, MAX_TITLE_LENGTH, stdin);
		new_book.title[strcspn(new_book.title, "\n")] = 0;
		printf("Enter author name: ");
		fgets(new_book.author, MAX_AUTHOR_LENGTH, stdin);
		new_book.author[strcspn(new_book.author, "\n")] = 0;
		new_book.id = num_books + 1;
		new_book.is_available = 1;
		library[num_books++] = new_book;
		printf("Book added successfully!\n");
	} 
	else {
		printf("Maximum capacity reached. Cannot add more books.\n");
	}
}


void displayBooks() {
	
	if (num_books == 0) {
		printf("No books in the library.\n");
	}
	else {
		printf("Library Catalog:\n");
		printf("%-5s %-30s %-20s\n", "ID", "Title", "Author");
		for (int i = 0; i < num_books; i++) {
			printf("%-5d %-30s %-20s\n", library[i].id, library[i].title, library[i].author);
		}
	}
}


void searchBook() {
	
	char search_title[MAX_TITLE_LENGTH];
	printf("Enter the title of the book to search: ");
	fgets(search_title, MAX_TITLE_LENGTH, stdin);
	search_title[strcspn(search_title, "\n")] = 0;
	int found = 0;
	for (int i = 0; i < num_books; i++) {
		
		if (strcmp(library[i].title, search_title) == 0) {
			printf("Book found:\n");
			printf("ID: %d\n", library[i].id);
			printf("Title: %s\n", library[i].title);
			printf("Author: %s\n", library[i].author);
			printf("Availability: %s\n", (library[i].is_available == 1) ? "Available" : "Not Available");
			found = 1;
			break;	
		}
	}
	if (!found) {
		printf("Book not found in the library.\n");
	}
}


void borrowBook() {
	
	int book_id, user_id;
	printf("Enter the user ID: ");
	scanf("%d", &user_id);
	getchar();
	if (user_id <= 0 || user_id > num_users) {
		printf("Invalid user ID.\n");
		return;
	}
	
	printf("Enter the ID of the book to borrow: ");
	scanf("%d", &book_id);
	getchar();
	int found = 0;
	for (int i = 0; i < num_books; i++) {
		if (library[i].id == book_id) {
			if (library[i].is_available == 1) {
				library[i].is_available = 0;
				printf("Book '%s' borrowed successfully by user '%s'.\n", library[i].title, users[user_id - 1].name);
			}
			else {
				printf("Book '%s' is currently not available.\n", library[i].title);
			}
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("Book with ID %d not found in the library.\n", book_id);
	}
}


void returnBook() {
	
	int book_id, user_id;
	printf("Enter the user ID: ");
	scanf("%d", &user_id);
	getchar();
	if (user_id <= 0 || user_id > num_users) {
		printf("Invalid user ID.\n");
		return;
	}
	
	
	printf("Enter the ID of the book to return: ");
	scanf("%d", &book_id);
	getchar();
	int found = 0;
	for (int i = 0; i < num_books; i ++) {
		
		if (library[i].id == book_id) {
			
			if (library[i].is_available == 0) {
				library[i].is_available = 1;
				printf("Book 's' returned successfully by user '%s'.\n", library[i].title, users[user_id - 1].name);
			}
			else {
				printf("This book is already available in the library.\n");
			}
			found = 1;
			break;
		}

	}
	if (!found) {
		printf("Book with ID %d not found in the library.\n", book_id);
	}	
}


int main(int argc, char *argv[]) {
	
	int choice;
	
	do {
		printf("\n Library Managment System Menu:\n");
		printf("1) Add a New Book\n");
		printf("2) Display All Books\n");
		printf("3) Search for a Book\n");
		printf("4) Borrow a Book\n");
		printf("5) Return a Book\n");
		printf("6) Add a New User\n");
		printf("7) Display All Users\n");
		printf("8) Exit\n");
		scanf("%d", &choice);
		getchar();
		
		switch (choice) {
			case 1:
				addBook();
				break;
			case 2:
				displayBooks();
				break;
			case 3:
				searchBook();
				break;
			case 4:
				borrowBook();
				break;
			case 5:
				returnBook();
				break;
			case 6:
				addUser();
				break;
			case 7:
				displayUsers();
				break;
			case 8:
				printf("Exiting the program.\n");
				break;
			default:
				printf("Invalid choice. Please enter a valid option");
		}
	}
	while (choice != 8);

	return 0;
}
