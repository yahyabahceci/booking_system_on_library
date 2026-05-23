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
    char* name;
    char* author;
    int age_limit;
    int price_per_week;
    float rented;
};

struct Rented {
    int R_ID;
    int C_ID;
    int B_ID;
    char* rented_date;
    int week;

};

struct Temp {
    int id;
    int age;
    int wallet;
    char name[50];
    char surname[50];
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
        return 0;
    }
    else {
        return menu_choosing;
    }
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
    printf("Please enter customer's id.");
    scanf("%d",&people.C_ID);
    printf("Enter the amount of money:");
    scanf("%d",&money);
    customers_txt = fopen("customers.txt","r");
    temp_customers = fopen("temp_customers.txt","w");

    if (customers_txt != NULL) {
        while (fscanf(customers_txt, "%d,%[^,],%[^,],%d,%d\n", &temp.id, temp.name, temp.surname, &temp.age, &temp.wallet) == 5) {
            if (people.C_ID == temp.id) {
                fprintf(temp_customers,"%d,%s,%s,%d,%d\n",temp.id,temp.name,temp.surname,temp.age,money);
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

    }
    else if (x==4) {

    }
    else if (x==5) {

    }
    else if (x==6) {

    }
    else if (x==7) {

    }
    else if (x==8) {

    }
    else if (x==9) {

    }
    else if (x==10) {

    }
    else if (x==11) {

    }
    else if (x==12) {

    }

    return 0;
}