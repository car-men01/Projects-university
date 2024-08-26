#pragma once

typedef struct {
    int day;
    int month;
    int year;
}Date;

typedef struct {
    char* name;
    char* category;
    int quantity;
    Date expiration_date;
}Product;

Product* create_product(char name[], char category[], int quantity, Date expiration_date);
void destroy_product(Product* product);
Product* copy_product(Product* product);
char* get_name(Product product);
char* get_category(Product product);
int get_quantity(Product product);
Date get_expiration_date(Product product);

