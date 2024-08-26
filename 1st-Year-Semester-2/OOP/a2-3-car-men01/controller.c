#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Creates the controller
/// \return the created controller
Controller* create_controller(Repository* repository, OperationsStack* undo_stack, OperationsStack* redo_stack)
{
    Controller* controller = malloc(sizeof(Controller));
    if (controller == NULL)
        return NULL;
    controller->repository = repository;
    controller->undo_stack = undo_stack;
    controller->redo_stack = redo_stack;
    return controller;
}

/// Frees the memory allocated to the controller
void destroy_controller(Controller* controller)
{
    destroy_repository(controller->repository);
    destroy_stack(controller->undo_stack);
    destroy_stack(controller->redo_stack);
    free(controller);
}

/// Adds a product and pushes it onto the undo stack
/// \param name product name
/// \param category product category
/// \param quantity product quantity
/// \param day product expiration day
/// \param month product expiration month
/// \param year product expiration year
void add_product(Controller* controller, char name[], char category[], int quantity, int day, int month, int year)
{
    int result = add_product_repository(controller->repository, name, category, quantity, day, month, year);
    if (result)
    {
        Product* product = get(controller->repository->products_list, get_position_of_product(controller->repository, name, category));
        Operation* operation = create_operation(product, "add");
        push(controller->undo_stack, operation);
    }
}

/// Updates a product and pushes it onto the undo stack
/// \param name product name
/// \param category product category
/// \param new_quantity product new quantity
/// \param new_day product new day
/// \param new_month product new month
/// \param new_year product new year
void update_product(Controller* controller, char name[], char category[], int quantity, int new_day, int new_month, int new_year)
{
    int result = update_product_repository(controller->repository, name, category, quantity, new_day, new_month, new_year);
    if(result)
    {
        Product* product = get(controller->repository->products_list, get_position_of_product(controller->repository, name, category));
        Operation* operation = create_operation(product, "update");
        push(controller->undo_stack, operation);
    }
}

/// Deletes a product and pushes it onto the undo stack
/// \param name product name
/// \param category product category
void delete_product(Controller* controller, char name[], char category[])
{
    int result = delete_product_repository(controller->repository, name, category);
    if (result) {
        Product* product = get(controller->repository->products_list, get_position_of_product(controller->repository, name, category));
        Operation* operation = create_operation(product, "delete");
        push(controller->undo_stack, operation);
    }
}

/// Sorts a list of products ascending by quantity
/// \param products_list the list of products to be sorted
void sort_ascending_by_quantity(DynamicArray* products_list)
{
    int size = get_size(products_list);
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            Product* product1 = get(products_list, i);
            Product* product2 = get(products_list, j);
            if (get_quantity(*product1) > get_quantity(*product2)) {
                set_elem_in_array(products_list, i, product2);
                set_elem_in_array(products_list, j, product1);
            }
        }
    }
}

/// Finds the products that contain a given string in their name
/// \param matched_products the list of products that contain the string
/// \param string_name the string to search by
void find_products(Controller* controller, DynamicArray* matched_products, char string_name[])
{
    int size = get_size(controller->repository->products_list);
    for (int i = 0; i < size; i++) {
        Product* current_product = get(controller->repository->products_list, i);
        if (strstr(get_name(*current_product), string_name)) {
            add_elem_to_array(matched_products, current_product);
        }
    }

    sort_ascending_by_quantity(matched_products);
}

/// The number of days between two given dates
/// \param date1 first date
/// \param date2 second date
/// \return the number of days between date1 and date2
int number_of_days_between_dates(Date date1, Date date2)
{
    int days1 = date1.year * 365 + date1.month * 30 + date1.day;
    int days2 = date2.year * 365 + date2.month * 30 + date2.day;
    if (days1 > days2)
        return days1 - days2;
    else
        return days2 - days1;
}

/// Checks the expiration date of the products to be less than a given number_of_days
/// \param same_category_products the list of the products from the same category
/// \param matched_products the list of the products that expire in the following number_of_days days
/// \param number_of_days the given number of days until the products expire
/// \param current_date the current date
void check_expiration_date(DynamicArray* same_category_products, DynamicArray* matched_products, int number_of_days, Date current_date)
{
    for (int i = 0; i < get_size(same_category_products); i++) {
        Product* current_product = get(same_category_products, i);
        if (number_of_days_between_dates(current_product->expiration_date, current_date) <= number_of_days) {
                add_elem_to_array(matched_products, current_product);
        }
    }
}

/// Finds the products from a given category that expire in the next number_of_days days
/// \param matched_products the list of products that match the criteria
/// \param input_category the input category to search by
/// \param number_of_days the number of days until the products expire
/// \param current_date the current date
void find_products_by_category(Controller* controller, DynamicArray* matched_products, char input_category[], int number_of_days, Date current_date)
{
    DynamicArray* same_category_products = create_dynamic_array(50, (destroyFunction) &destroy_product);
    DynamicArray* products_list = get_all_products(controller->repository);
    for (int i = 0; i < products_list->size; i++) {
        Product* current_product = get(products_list, i);
        if (strstr(get_category(*current_product), input_category)) {
            add_elem_to_array(same_category_products, current_product);
        }
    }

    check_expiration_date(same_category_products, matched_products, number_of_days, current_date);
}

/// Checks the user input name and category of the product
/// \param name input name
/// \param category input category
/// \return 1 if the input is validated or 0 otherwise
int check_input_name_category(Controller* controller, char name[], char category[])
{
    DynamicArray* products_list = get_all_products(controller->repository);
    /// checks if the product with the given name and category exists
    for (int i = 0; i < products_list->size; i++) {
        Product* current_product = get(products_list, i);
        if ((strcmp(get_name(*current_product), name) == 0) && (strcmp(get_category(*current_product), category) == 0)) {
            return 1;
        }
    }
    return 0;
}

/// Undo the last operation
/// \return 1 if the undo was successful or 0 otherwise
int undo(Controller* controller)
{
    if (is_empty(controller->undo_stack))
        return 0;
    Operation* operation = pop(controller->undo_stack);

    if (strcmp(get_operation_type(operation), "add") == 0) {
        Product* product = get_product(operation);
        char name[31], category[31];
        strcpy(name, get_name(*product));
        strcpy(category, get_category(*product));
        delete_product_repository(controller->repository, name, category);
    }

    else if (strcmp(get_operation_type(operation), "delete") == 0) {
        Product* product = get_product(operation);
        char name[31], category[31];
        int quantity, day, month, year;
        strcpy(name, get_name(*product));
        strcpy(category, get_category(*product));
        quantity = get_quantity(*product);
        day = get_expiration_date(*product).day;
        month = get_expiration_date(*product).month;
        year = get_expiration_date(*product).year;
        add_product_repository(controller->repository, name, category, quantity, day, month, year);
    }

    else if (strcmp(get_operation_type(operation), "update") == 0) {
        Product* product = get_product(operation);
        update_product_repository(controller->repository, get_name(*product), get_category(*product), get_quantity(*product),
                                  get_expiration_date(*product).day, get_expiration_date(*product).month,
                                  get_expiration_date(*product).year);
    }

    push(controller->redo_stack, operation);
    return 1;
}

/// Redo the last operation
/// \return 1 if the redo was successful or 0 otherwise
int redo(Controller* controller)
{
    if (is_empty(controller->redo_stack))
        return 0;
    Operation* operation = pop(controller->redo_stack);

    if (strcmp(get_operation_type(operation), "add") == 0) {
        Product* product = get_product(operation);
        add_product_repository(controller->repository, get_name(*product), get_category(*product), get_quantity(*product),
                              get_expiration_date(*product).day, get_expiration_date(*product).month,
                              get_expiration_date(*product).year);
    }

    else if (strcmp(get_operation_type(operation), "delete") == 0) {
        Product* product = get_product(operation);
        delete_product_repository(controller->repository, get_name(*product), get_category(*product));
    }

    else if (strcmp(get_operation_type(operation), "update") == 0) {
        Product* product = get_product(operation);
        update_product_repository(controller->repository, get_name(*product), get_category(*product), get_quantity(*product),
                                  get_expiration_date(*product).day, get_expiration_date(*product).month,
                                  get_expiration_date(*product).year);
    }

    push(controller->undo_stack, operation);
    return 1;
}
