#include <stdio.h>

struct Customer {
    int C_ID;
    char* name;
    char* surname;
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
}

int main() {

    greeting();

    return 0;
}