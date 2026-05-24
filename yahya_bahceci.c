#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* customers_txt;
FILE* books_txt;
FILE* rented_txt;
FILE* history_txt;

struct Customer {
    int C_ID;
    char name[50];
    char surname[50];
    int age;
    int wallet;
};

struct Book {
    int B_ID;
    char name[100];
    char author[50];
    int age_limit;
    int price_per_week;
    int rented;

};

struct Rented {
    int R_ID;
    int C_ID;
    int B_ID;
    char rented_date[50];
    int week;

};

struct Temp {
    int id;
    int cid;
    int bid;
    int age;
    int wallet;
    int age_limit;
    int money;
    int rented;
    int week;
    char date[50];
    char name[50];
    char surname[50];
    char author[50];
    char book[100];;
};

int greeting() {
    int menu_choosing;
    printf("Please choose one operation.\n");
    printf("1. Create New Customer\n");
    printf("2. Deposit Money to the Customer\n");
    printf("3. Add New Book\n");
    printf("4. Rent A Book\n");
    printf("5. Delivery A Book\n");
    printf("6. Burn Book\n");
    printf("7. Update Customer and Book Information\n");
    printf("8. List of Customers Who Rent a Book\n");
    printf("9. List of Customers\n");
    printf("10. List of Books\n");
    printf("11. Search Book\n");
    printf("12. Exit\n");
    printf("--->");
    scanf("%d",&menu_choosing);

    if (menu_choosing<=0 || menu_choosing>=13) {
        printf("Please choose correct menu!!!");
    }
    else {
        return menu_choosing;
    }
    return 0;
}

int create_new_customers() {
    struct Customer people;
    struct Temp temp;
    int last_id=0;
    int c;
    char age_buffer[5];

    while ((c = getchar()) != '\n' && c != EOF)

    printf("Please enter new customer.\n");
    printf("Name: ");
    fgets(people.name,sizeof(people.name),stdin);
    people.name[strcspn(people.name, "\n")] = '\0';
    printf("Surname: ");
    fgets(people.surname,sizeof(people.surname),stdin);
    people.surname[strcspn(people.surname, "\n")] = '\0';
    printf("Age: ");
    fgets(age_buffer,sizeof(age_buffer),stdin);
    people.age = atoi(age_buffer);


    customers_txt = fopen("customers.txt","r");

    if (customers_txt != NULL) {
        while (fscanf(customers_txt, "%d,%[^,],%[^,],%d,%d\n", &temp.id, temp.name, temp.surname, &temp.age, &temp.wallet) == 5) {
            last_id = temp.id;
            if (strcmp(temp.name,people.name) == 0 && strcmp(temp.surname,people.surname) == 0){
                printf("This customer exists and He/She has %d C_ID(Customer ID).",temp.id);
                return 1;
            }
        }
        fclose(customers_txt);
    }
    people.C_ID = last_id+1;
    people.wallet = 0;

    customers_txt = fopen("customers.txt","a");
    fprintf(customers_txt,"%d,%s,%s,%d,%d\n",people.C_ID,people.name,people.surname,people.age,people.wallet);
    fclose(customers_txt);

    printf("A new customer has been registered. C_ID(Customer ID)is %d.",people.C_ID);

    return 0;
}

int deposit_money() {
    FILE* temp_customers;
    struct Customer people;
    struct Temp temp;
    int money = 0;
    printf("DEPOSIT MONEY\n");
    printf("Please enter customer's id: ");
    scanf("%d",&people.C_ID);
    printf("Enter the amount of money:");
    scanf("%d",&money);
    customers_txt = fopen("customers.txt","r");
    temp_customers = fopen("temp_customers.txt","w");

    if (customers_txt != NULL) {
        while (fscanf(customers_txt, "%d,%[^,],%[^,],%d,%d\n", &temp.id, temp.name, temp.surname, &temp.age, &temp.wallet) == 5) {
            if (people.C_ID == temp.id) {
                fprintf(temp_customers,"%d,%s,%s,%d,%d\n",temp.id,temp.name,temp.surname,temp.age,temp.wallet+money);
            }
            else {
                fprintf(temp_customers,"%d,%s,%s,%d,%d\n",temp.id,temp.name,temp.surname,temp.age,temp.wallet);
            }
        }
    }
    fclose(customers_txt);
    fclose(temp_customers);

    remove("customers.txt");
    rename("temp_customers.txt","customers.txt");
    printf("Deposit successful.");
    return 0;
}

int add_new_book() {
    struct Book book;
    struct Temp temp;
    int last_id = 0;
    int c;
    char age_buffer[5];
    char money_buffer[10];
    while ((c = getchar()) != '\n' && c != EOF)

    printf("Please enter new book.\n");
    printf("The name of the book: ");
    fgets(book.name,sizeof(book.name),stdin);
    book.name[strcspn(book.name,"\n")] = '\0';
    printf("The name of the author: ");
    fgets(book.author,sizeof(book.author),stdin);
    book.author[strcspn(book.author,"\n")] = '\0';
    printf("Enter the age limit of the book: ");
    fgets(age_buffer,sizeof(age_buffer),stdin);
    age_buffer[strcspn(age_buffer,"\n")] = '\0';
    book.age_limit = atoi(age_buffer);
    printf("Please enter price per week: ");
    fgets(money_buffer,sizeof(money_buffer),stdin);
    age_buffer[strcspn(money_buffer,"\n")] = '\0';
    book.price_per_week = atoi(money_buffer);

    books_txt = fopen("books.txt","r");

    if (books_txt != NULL) {
        while (fscanf(books_txt,"%d,%[^,],%[^,],%d,%d,%d\n", &temp.id, temp.book, temp.author, &temp.age_limit, &temp.money, &temp.rented) == 6) {
            last_id = temp.id;
            if (strcmp(temp.book,book.name) == 0 && strcmp(temp.author,book.author) == 0) {
                printf("This book exists and its B_ID (Book ID) is %d.",temp.id);
                return 1;
            }
        }
        fclose(books_txt);
    }
    book.B_ID = last_id + 1;
    book.rented = 0;

    books_txt = fopen("books.txt","a");
    fprintf(books_txt,"%d,%s,%s,%d,%d,%d\n",book.B_ID,book.name,book.author,book.age_limit,book.price_per_week,book.rented);
    fclose(books_txt);

    printf("A new book has been added to system. B_ID (Book ID) is %d",book.B_ID);

    return 0;
}

int rent_book() {
    FILE* temp_books;
    FILE* books_read_txt;
    struct Book book;
    struct Temp temp;
    struct Rented rented;
    struct Customer people;
    int c;
    int last_id = 0;

    while ((c = getchar()) != '\n' && c != EOF);

    printf("Please enter your C_ID(Customer ID): ");
    scanf("%d",&rented.C_ID);
    printf("Please choose your book and enter B_ID(Book ID): ");
    scanf("%d",&rented.B_ID);
    printf("How many weeks will you rent?: ");
    scanf("%d",&rented.week);

    rented_txt = fopen("rented.txt","r");

    if (rented_txt != NULL) {
        while (fscanf(rented_txt, "%d,%d,%d,%[^,],%d\n", &temp.id, &temp.cid, &temp.bid, temp.date, &temp.week) == 5) {
            last_id = temp.id;
        }
        fclose(rented_txt);
    }
    rented.R_ID = last_id + 1;

    books_txt = fopen("books.txt","r");

    if (books_txt != NULL) {
        while (fscanf(books_txt,"%d,%[^,],%[^,],%d,%d,%d\n", &temp.id, temp.book, temp.author, &temp.age_limit, &temp.money, &temp.rented) == 6) {
            if (temp.id == rented.B_ID) {
                int book_money = temp.money;
                int book_age = temp.age_limit;
                if (temp.rented==0) {
                    customers_txt = fopen("customers.txt","r");
                    while (fscanf(customers_txt, "%d,%[^,],%[^,],%d,%d\n", &people.C_ID, people.name, people.surname, &people.age, &people.wallet) == 5) {
                        if (people.C_ID == rented.C_ID) {
                            if (book_money * rented.week <= people.wallet) {
                                if (book_age <= people.age) {
                                    books_read_txt = fopen("books.txt", "r");
                                    temp_books = fopen("temp_books.txt", "w");

                                    if (books_read_txt != NULL && temp_books != NULL) {
                                        while(fscanf(books_read_txt, "%d,%[^,],%[^,],%d,%d,%d\n", &book.B_ID, book.name, book.author, &book.age_limit, &book.price_per_week, &book.rented) == 6) {
                                            if (rented.B_ID == book.B_ID) {
                                                fprintf(temp_books, "%d,%s,%s,%d,%d,1\n", book.B_ID, book.name, book.author, book.age_limit, book.price_per_week);
                                            }
                                            else {
                                                fprintf(temp_books, "%d,%s,%s,%d,%d,%d\n", book.B_ID, book.name, book.author, book.age_limit, book.price_per_week, book.rented);
                                            }
                                        }
                                        fclose(books_read_txt);
                                        fclose(temp_books);
                                    }

                                    printf("Please enter today's date: ");
                                    while ((c = getchar()) != '\n' && c != EOF);

                                    fgets(rented.rented_date, sizeof(rented.rented_date), stdin);
                                    rented.rented_date[strcspn(rented.rented_date, "\n")] = '\0';

                                    rented_txt = fopen("rented.txt", "a");
                                    if (rented_txt != NULL) {
                                        fprintf(rented_txt, "%d,%d,%d,%s,%d\n", rented.R_ID, rented.C_ID, rented.B_ID, rented.rented_date, rented.week);
                                        fclose(rented_txt);
                                    }
                                }
                                else {
                                    printf("You can not rent because of age limit.");
                                }
                            }
                            else {
                                printf("You do not have enough money to rent this book.");
                                return 2;
                            }
                        }
                    }
                }
                else {
                    printf("%s was rented.",temp.book);
                    return 3;
                }
            }
        }
        fclose(books_txt);
        remove("books.txt");
        rename("temp_books.txt", "books.txt");
    }

    return 0;
}

int delivery_book() {
    FILE* temp_rented;
    FILE* temp_books;
    FILE* temp_customers;
    struct Temp temp;
    int r_id, weeks_diff, c_id, b_id;
    int book_price = 0;
    int found = 0;

    printf("DELIVERY A BOOK\n");
    printf("Enter R_ID: ");
    scanf("%d", &r_id);
    printf("Enter remaining weeks (positive number for early) or late weeks (negative number for late) [0 if exact time]: ");
    scanf("%d", &weeks_diff);

    rented_txt = fopen("rented.txt", "r");
    temp_rented = fopen("temp_rented.txt", "w");
    history_txt = fopen("history.txt", "a");

    if (rented_txt != NULL) {
        while (fscanf(rented_txt, "%d,%d,%d,%[^,],%d\n", &temp.id, &temp.cid, &temp.bid, temp.date, &temp.week) == 5) {
            if (temp.id == r_id) {
                found = 1;
                c_id = temp.cid;
                b_id = temp.bid;
                fprintf(history_txt, "%d,%d,%d,%s,%d\n", temp.id, temp.cid, temp.bid, temp.date, temp.week);
            } else {
                fprintf(temp_rented, "%d,%d,%d,%s,%d\n", temp.id, temp.cid, temp.bid, temp.date, temp.week);
            }
        }
        fclose(rented_txt);
        fclose(temp_rented);
        fclose(history_txt);
        remove("rented.txt");
        rename("temp_rented.txt", "rented.txt");
    }

    if (!found) {
        printf("This R_ID could not be found.\n");
        return 1;
    }

    books_txt = fopen("books.txt", "r");
    temp_books = fopen("temp_books.txt", "w");
    if (books_txt != NULL) {
        while (fscanf(books_txt,"%d,%[^,],%[^,],%d,%d,%d\n", &temp.id, temp.book, temp.author, &temp.age_limit, &temp.money, &temp.rented) == 6) {
            if (temp.id == b_id) {
                book_price = temp.money;
                fprintf(temp_books, "%d,%s,%s,%d,%d,0\n", temp.id, temp.book, temp.author, temp.age_limit, temp.money);
            } else {
                fprintf(temp_books, "%d,%s,%s,%d,%d,%d\n", temp.id, temp.book, temp.author, temp.age_limit, temp.money, temp.rented);
            }
        }
        fclose(books_txt);
        fclose(temp_books);
        remove("books.txt");
        rename("temp_books.txt", "books.txt");
    }

    customers_txt = fopen("customers.txt", "r");
    temp_customers = fopen("temp_customers.txt", "w");
    if (customers_txt != NULL) {
        while (fscanf(customers_txt, "%d,%[^,],%[^,],%d,%d\n", &temp.id, temp.name, temp.surname, &temp.age, &temp.wallet) == 5) {
            if (temp.id == c_id) {
                int new_wallet = temp.wallet + (weeks_diff * book_price);
                fprintf(temp_customers, "%d,%s,%s,%d,%d\n", temp.id, temp.name, temp.surname, temp.age, new_wallet);
            } else {
                fprintf(temp_customers, "%d,%s,%s,%d,%d\n", temp.id, temp.name, temp.surname, temp.age, temp.wallet);
            }
        }
        fclose(customers_txt);
        fclose(temp_customers);
        remove("customers.txt");
        rename("temp_customers.txt", "customers.txt");
    }

    printf("Book delivered successfully. Wallet adjusted by %d TL.\n", (weeks_diff * book_price));
    return 0;
}

int burn_book() {
    FILE* temp_books;
    struct Temp temp;
    int b_id;
    int found = 0;

    printf("BURN A BOOK\n");
    printf("Enter B_ID to burn: ");
    scanf("%d", &b_id);

    books_txt = fopen("books.txt", "r");
    temp_books = fopen("temp_books.txt", "w");

    if (books_txt != NULL) {
        while (fscanf(books_txt,"%d,%[^,],%[^,],%d,%d,%d\n", &temp.id, temp.book, temp.author, &temp.age_limit, &temp.money, &temp.rented) == 6) {
            if (temp.id == b_id) {
                found = 1;
                if (temp.rented == 1) {
                    printf("You cannot burn a book that is currently rented.\n");
                    fprintf(temp_books, "%d,%s,%s,%d,%d,%d\n", temp.id, temp.book, temp.author, temp.age_limit, temp.money, temp.rented);
                } else {
                    printf("Book '%s' has been successfully burned.\n", temp.book);
                }
            } else {
                fprintf(temp_books, "%d,%s,%s,%d,%d,%d\n", temp.id, temp.book, temp.author, temp.age_limit, temp.money, temp.rented);
            }
        }
        fclose(books_txt);
        fclose(temp_books);
        remove("books.txt");
        rename("temp_books.txt", "books.txt");
    }

    if (!found) {
        printf("Book not found.\n");
    }
    return 0;
}

int update_information() {
    int choice;
    int c;
    printf("1. Update Customer Information\n");
    printf("2. Update Book Information\n");
    printf("---> ");
    scanf("%d", &choice);
    while ((c = getchar()) != '\n' && c != EOF);

    if (choice == 1) {
        FILE* temp_customers;
        struct Customer people;
        struct Temp temp;
        char age_buffer[5];
        int found = 0;

        printf("Enter C_ID to update: ");
        scanf("%d", &people.C_ID);
        while ((c = getchar()) != '\n' && c != EOF);

        printf("New Name: ");
        fgets(people.name, sizeof(people.name), stdin);
        people.name[strcspn(people.name, "\n")] = '\0';
        printf("New Surname: ");
        fgets(people.surname, sizeof(people.surname), stdin);
        people.surname[strcspn(people.surname, "\n")] = '\0';
        printf("New Age: ");
        fgets(age_buffer, sizeof(age_buffer), stdin);
        people.age = atoi(age_buffer);

        customers_txt = fopen("customers.txt", "r");
        temp_customers = fopen("temp_customers.txt", "w");

        if (customers_txt != NULL) {
            while (fscanf(customers_txt, "%d,%[^,],%[^,],%d,%d\n", &temp.id, temp.name, temp.surname, &temp.age, &temp.wallet) == 5) {
                if (temp.id == people.C_ID) {
                    found = 1;
                    fprintf(temp_customers, "%d,%s,%s,%d,%d\n", temp.id, people.name, people.surname, people.age, temp.wallet);
                } else {
                    fprintf(temp_customers, "%d,%s,%s,%d,%d\n", temp.id, temp.name, temp.surname, temp.age, temp.wallet);
                }
            }
            fclose(customers_txt);
            fclose(temp_customers);
            remove("customers.txt");
            rename("temp_customers.txt", "customers.txt");
        }
        if (found) printf("Customer information updated.\n");
        else printf("Customer not found.\n");

    } else if (choice == 2) {
        FILE* temp_books;
        struct Book book;
        struct Temp temp;
        char age_buffer[5];
        char money_buffer[10];
        int found = 0;

        printf("Enter B_ID to update: ");
        scanf("%d", &book.B_ID);
        while ((c = getchar()) != '\n' && c != EOF);

        printf("New Book Name: ");
        fgets(book.name, sizeof(book.name), stdin);
        book.name[strcspn(book.name, "\n")] = '\0';
        printf("New Author Name: ");
        fgets(book.author, sizeof(book.author), stdin);
        book.author[strcspn(book.author, "\n")] = '\0';
        printf("New Age Limit: ");
        fgets(age_buffer, sizeof(age_buffer), stdin);
        book.age_limit = atoi(age_buffer);
        printf("New Price Per Week: ");
        fgets(money_buffer, sizeof(money_buffer), stdin);
        book.price_per_week = atoi(money_buffer);

        books_txt = fopen("books.txt", "r");
        temp_books = fopen("temp_books.txt", "w");

        if (books_txt != NULL) {
            while (fscanf(books_txt,"%d,%[^,],%[^,],%d,%d,%d\n", &temp.id, temp.book, temp.author, &temp.age_limit, &temp.money, &temp.rented) == 6) {
                if (temp.id == book.B_ID) {
                    found = 1;
                    fprintf(temp_books, "%d,%s,%s,%d,%d,%d\n", temp.id, book.name, book.author, book.age_limit, book.price_per_week, temp.rented);
                } else {
                    fprintf(temp_books, "%d,%s,%s,%d,%d,%d\n", temp.id, temp.book, temp.author, temp.age_limit, temp.money, temp.rented);
                }
            }
            fclose(books_txt);
            fclose(temp_books);
            remove("books.txt");
            rename("temp_books.txt", "books.txt");
        }
        if (found) printf("Book information updated.\n");
        else printf("Book not found.\n");
    } else {
        printf("Invalid choice.\n");
    }
    return 0;
}

int list_rented_customers() {
    struct Temp temp;
    struct Temp temp_c;
    int printed = 0;

    printf("\n--- List of Customers Who Rent a Book ---\n");
    rented_txt = fopen("rented.txt", "r");
    if (rented_txt != NULL) {
        while (fscanf(rented_txt, "%d,%d,%d,%[^,],%d\n", &temp.id, &temp.cid, &temp.bid, temp.date, &temp.week) == 5) {
            customers_txt = fopen("customers.txt", "r");
            if (customers_txt != NULL) {
                while (fscanf(customers_txt, "%d,%[^,],%[^,],%d,%d\n", &temp_c.id, temp_c.name, temp_c.surname, &temp_c.age, &temp_c.wallet) == 5) {
                    if (temp.cid == temp_c.id) {
                        printf("Customer ID: %d | Name: %s %s | Rented Book ID: %d\n", temp_c.id, temp_c.name, temp_c.surname, temp.bid);
                        printed = 1;
                        break;
                    }
                }
                fclose(customers_txt);
            }
        }
        fclose(rented_txt);
    }
    if (printed == 0) {
        printf("There are no customers who rent a book right now.\n");
    }
    return 0;
}

int list_customers() {
    struct Temp temp;
    printf("\n--- List of Customers ---\n");
    customers_txt = fopen("customers.txt", "r");
    if (customers_txt != NULL) {
        while (fscanf(customers_txt, "%d,%[^,],%[^,],%d,%d\n", &temp.id, temp.name, temp.surname, &temp.age, &temp.wallet) == 5) {
            printf("C_ID: %d | Name: %s %s | Age: %d | Wallet: %d TL\n", temp.id, temp.name, temp.surname, temp.age, temp.wallet);
        }
        fclose(customers_txt);
    }
    return 0;
}

int list_books() {
    struct Temp temp;
    printf("\n--- List of Books ---\n");
    books_txt = fopen("books.txt", "r");
    if (books_txt != NULL) {
        while (fscanf(books_txt,"%d,%[^,],%[^,],%d,%d,%d\n", &temp.id, temp.book, temp.author, &temp.age_limit, &temp.money, &temp.rented) == 6) {
            printf("B_ID: %d | Name: %s | Author: %s | Age Limit: %d | Price: %d TL/week | Rented: %d\n",
                   temp.id, temp.book, temp.author, temp.age_limit, temp.money, temp.rented);
        }
        fclose(books_txt);
    }
    return 0;
}

int search_book() {
    int choice;
    int c;
    struct Temp temp;
    char search_str[100];
    int search_age;
    int found = 0;

    printf("1. Search by Name\n");
    printf("2. Search by Author\n");
    printf("3. Search by Age Limit\n");
    printf("---> ");
    scanf("%d", &choice);
    while ((c = getchar()) != '\n' && c != EOF);

    books_txt = fopen("books.txt", "r");
    if (books_txt == NULL) return 1;

    if (choice == 1 || choice == 2) {
        printf("Enter search text: ");
        fgets(search_str, sizeof(search_str), stdin);
        search_str[strcspn(search_str, "\n")] = '\0';
    } else if (choice == 3) {
        printf("Enter age limit: ");
        scanf("%d", &search_age);
    }

    printf("\n--- Search Results ---\n");
    while (fscanf(books_txt,"%d,%[^,],%[^,],%d,%d,%d\n", &temp.id, temp.book, temp.author, &temp.age_limit, &temp.money, &temp.rented) == 6) {
        int match = 0;
        if (choice == 1 && strstr(temp.book, search_str) != NULL) match = 1;
        else if (choice == 2 && strstr(temp.author, search_str) != NULL) match = 1;
        else if (choice == 3 && temp.age_limit == search_age) match = 1;

        if (match) {
            printf("B_ID: %d | Name: %s | Author: %s | Age Limit: %d | Price: %d TL/week | Rented: %d\n",
                   temp.id, temp.book, temp.author, temp.age_limit, temp.money, temp.rented);
            found = 1;
        }
    }
    fclose(books_txt);

    if (!found) printf("No matching books found.\n");
    return 0;
}


int main() {

    customers_txt = fopen("customers.txt", "r");
    books_txt = fopen("books.txt", "r");
    rented_txt = fopen("rented.txt", "r");
    history_txt = fopen("history.txt", "r");

    if (customers_txt==NULL) {
        customers_txt = fopen("customers.txt","w");
        fclose(customers_txt);
    }
    if (books_txt==NULL) {
        books_txt = fopen("books.txt","w");
        fclose(books_txt);
    }
    if (rented_txt==NULL) {
        rented_txt = fopen("rented.txt","w");
        fclose(rented_txt);
    }
    if (history_txt==NULL) {
        history_txt = fopen("history.txt","w");
        fclose(history_txt);
    }


    while (1) {
        int x = greeting();

        if (x==1) {
            create_new_customers();
        }
        else if (x==2) {
            deposit_money();
        }
        else if (x==3) {
            add_new_book();
        }
        else if (x==4) {
            rent_book();
        }
        else if (x==5) {
            delivery_book();
        }
        else if (x==6) {
            burn_book();
        }
        else if (x==7) {
            update_information();
        }
        else if (x==8) {
            list_rented_customers();
        }
        else if (x==9) {
            list_customers();
        }
        else if (x==10) {
            list_books();
        }
        else if (x==11) {
            search_book();
        }
        else if (x==12) {
            break;
        }
    }
    return 0;

}