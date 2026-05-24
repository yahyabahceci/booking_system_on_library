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
    printf("7. Update Customer Information\n");
    printf("8. Update Book Information\n");
    printf("9. List of Customers Who Rent a Book\n");
    printf("10. List of Customers\n");
    printf("11. List of Books\n");
    printf("12. Search Book\n");
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

    return 0;
}