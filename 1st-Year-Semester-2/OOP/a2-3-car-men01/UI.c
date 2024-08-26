#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

UI* create_ui(Controller* controller)
{
    UI* ui = malloc(sizeof(UI));
    if(ui == NULL)
        return NULL;
    ui->controller = controller;
    return ui;
}

void destroy_ui(UI* ui)
{
    destroy_controller(ui->controller);
    free(ui);
}


/// Prints the console menu
void print_menu()
{
    printf("INTELLIGENT REFRIGERATOR\n");
    printf("1. Add a product\n");
    printf("2. Delete a product\n");
    printf("3. Update a product\n");
    printf("4. Display all products\n");
    printf("5. Display all products by given string\n");
    printf("6. Display all products of a given category\n");
    printf("7. Undo last operation\n");
    printf("8. Redo last operation\n");
    printf("9. Exit the program\n");

}

int read_integer_number(const char* message)
{
    char s[16];
    int res = 0;
    int flag = 0;
    int r = 0;

    while (flag == 0)
    {
        printf(message);
        scanf("%s", s);

        r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
        flag = (r == 1);
        if (flag == 0)
            printf("Error reading number!\n");
    }
    return res;
}

void add_product_ui(UI* ui)
{
    char name[31], category[31];
    int quantity, month, day, year;

    printf("Add a product to the fridge!\n\n");
    printf("Name:");
    scanf(" %[^\n]", name);

    printf("Category:");
    scanf("%s", category);

    printf("Quantity:");
    scanf("%d", &quantity);

    printf("Expiration date:\n");
    printf("Day:");
    scanf("%d", &day);
    printf("Month:");
    scanf("%d", &month);
    printf("Year:");
    scanf("%d", &year);

    add_product(ui->controller, name, category, quantity, day, month, year);

    printf("\nThe product was added successfully!\n\n");
}

void delete_product_ui(UI* ui)
{
    char name[31], category[31];
    printf("Remove a product from the fridge!\n\n");
    printf("Name:");
    scanf(" %[^\n]", name);
    printf("Category:");
    scanf("%s", category);

    if (check_input_name_category(ui->controller, name, category)) {

        delete_product(ui->controller, name, category);

        printf("\nThe product was deleted successfully!\n\n");
    }
    else
        printf("\nThe product with the name %s from the category %s doesn't exist in the refrigerator.\n\n", name, category);
}

void update_product_ui(UI* ui)
{
    char name[31], category[31];
    int new_quantity, new_month, new_year, new_day;

    printf("Update a product from the fridge!\n\n");
    printf("Name:");
    scanf(" %[^\n]", name);
    printf("Category:");
    scanf("%s", category);

    if (check_input_name_category(ui->controller, name, category)) {
        printf("New quantity:");
        scanf("%d", &new_quantity);
        printf("New expiration date:\n");
        printf("Day:");
        scanf("%d", &new_day);
        printf("Month:");
        scanf("%d", &new_month);
        printf("Year:");
        scanf("%d", &new_year);

        update_product(ui->controller, name, category, new_quantity, new_day, new_month, new_year);

        printf("\nThe product was updated successfully!\n\n");
    }
    else
        printf("\nThe product with the name %s from the category %s doesn't exist in the refrigerator.\n\n", name, category);
}

void display_all_products(DynamicArray* products_list)
{
    for (int i = 0; i < get_size(products_list); i++) {
        Product* current_product = get(products_list, i);
        printf("%d - ", i + 1);
        printf("Name: %s, Category: %s, Quantity: %d, Expiration date: %d.%d.%d\n", current_product->name,
               current_product->category, current_product->quantity,
               current_product->expiration_date.day, current_product->expiration_date.month,
               current_product->expiration_date.year);
    }
    printf("\n");
}

void display_by_string(UI* ui)
{
    int size_found = 0;
    char string_name[31];
    DynamicArray* matched_products = create_dynamic_array(50, (destroyFunction) &destroy_product);

    printf("Search for a product from the fridge!\n\n");
    printf("Enter a string to search by:");

    scanf(" %[^\n]", string_name);

    /// empty string doesn't work on scanf so i chose the "0" option to take into consideration all products
    if (strcmp(string_name, "0") == 0)
        strcpy(string_name, "");

    find_products(ui->controller, matched_products, string_name);

    update_size(matched_products, &size_found);

    if (size_found > 0) {
        printf("\nThe products containing the string %s in their name are:\n", string_name);
        display_all_products(matched_products);
    }
    else if (size_found == 0)
        printf("\nThere are no products containing the string %s in their name.\n\n", string_name);
}

void display_by_category(UI* ui)
{
    int size_found = 0, number_of_days;
    char input_category[31];
    DynamicArray* matched_products = create_dynamic_array(50, (destroyFunction) &destroy_product);
    Date current_date;

    printf("Search for a product from the fridge!\n\n");
    printf("Enter a category to search by:");
    scanf(" %[^\n]", input_category);
    printf("\nEnter the current day:");
    scanf("%d", &current_date.day);
    printf("Enter the current month:");
    scanf("%d", &current_date.month);
    printf("Enter the current year:");
    scanf("%d", &current_date.year);
    printf("\nEnter the number of days between the expiration dates and the current date:");
    scanf("%d", &number_of_days);

    /// empty string doesn't work on scanf so i chose the "0" option to take into consideration all products
    if (strcmp(input_category, "0") == 0)
        strcpy(input_category, "");

    find_products_by_category(ui->controller, matched_products, input_category, number_of_days, current_date);

    update_size(matched_products, &size_found);

    if (size_found > 0) {
        if (strcmp(input_category, "") != 0) {
            printf("\nThe products from the category %s that expire in the next %d days are:\n", input_category,
                   number_of_days);
            display_all_products(matched_products);
        }
        else {
            printf("\nThe products that expire in the next %d days are:\n", number_of_days);
            display_all_products(matched_products);
        }
    }
    else if (size_found == 0)
        printf("\nThere are no products from the category %s.\n\n", input_category);
}
