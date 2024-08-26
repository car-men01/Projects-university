#include "repository.h"
#include <stdlib.h>
#include <string.h>

/// Creates the repository
/// \return the created repository
Repository* create_repository()
{
    Repository* repository = malloc(sizeof(Repository));
    if (repository == NULL)
        return NULL;
    repository->products_list = create_dynamic_array(50, (destroyFunction) &destroy_product);
    return repository;
}

/// Frees the memory allocated to the repository
void destroy_repository(Repository* repository)
{
    if (repository == NULL)
        return;
    destroy_dynamic_array(repository->products_list);
    free(repository);
}

/// Gets the list of products from the repository
/// \return The list of products
DynamicArray* get_all_products(Repository* repository)
{
    return repository->products_list;
}

/// Gets the position of the product in the repository
/// \param name the name of the products
/// \param category the category of the product
/// \return the position of the product in the repository (or -1 if the products doesn't exist)
int get_position_of_product(Repository* repository, char name[], char category[])
{
    for (int i = 0; i < get_size(repository->products_list); i++) {
        Product* current_product = get(repository->products_list, i);
        if ((strcmp(get_name(*current_product), name) == 0) && (strcmp(get_category(*current_product), category) == 0)) {
            return i;
        }
    }
    return -1;
}

/// Adds a product to the repository
/// \param name product name
/// \param category product category
/// \param quantity product quantity
/// \param day product expiration day
/// \param month product expiration month
/// \param year product expiration year
/// \return 1 if the product was added successfully or 0 otherwise
int add_product_repository(Repository* repository, char name[], char category[], int quantity, int day, int month, int year)
{
    if (repository == NULL || name == NULL || category == NULL || quantity < 0 || day < 1 || day > 31 || month < 1 ||
        month > 12 || year < 0)
        return 0;
    int found = 0;
    /// search if the product already exists
    for (int i = 0; i < get_size(repository->products_list); i++) {
        Product* current_product = get(repository->products_list, i);
        if ((strcmp(get_name(*current_product), name) == 0) &&
            (strcmp(get_category(*current_product), category) == 0)) {
            current_product->quantity += quantity;
            update_elem_in_array(repository->products_list, i, current_product);
            found = 1;
        }
    }
    if (found == 0) {
        Date expiration_date = {day, month, year};
        Product *new_product = create_product(name, category, quantity, expiration_date);
        add_elem_to_array(repository->products_list, new_product);
    }
    return 1;
}

/// Deletes a product from the repository
/// \param name product name
/// \param category product category
/// \return 1 if the product was deleted successfully or 0 otherwise
int delete_product_repository(Repository* repository, char name[], char category[])
{
    if (repository == NULL)
        return 0;
    for (int i = 0; i < get_size(repository->products_list); i++) {
        Product* current_product = get(repository->products_list, i);
        if ((strcmp(get_name(*current_product), name) == 0) && (strcmp(get_category(*current_product), category) == 0)) {
            delete_elem_from_array(repository->products_list, i);
        }
    }
    return 1;
}

/// Updates an existing product in the repository
/// \param name product name
/// \param category product category
/// \param new_quantity product new quantity
/// \param new_day product new day
/// \param new_month product new month
/// \param new_year product new year
/// \return 1 if the product was updated successfully or 0 otherwise
int update_product_repository(Repository* repository, char name[], char category[], int new_quantity,
                               int new_day, int new_month, int new_year)
{
    if (repository == NULL)
        return 0;
    for (int i = 0; i < get_size(repository->products_list); i++) {
        Product* current_product = get(repository->products_list, i);
        if ((strcmp(get_name(*current_product), name) == 0) && (strcmp(get_category(*current_product), category) == 0)) {
            current_product->quantity = new_quantity;
            current_product->expiration_date.day = new_day;
            current_product->expiration_date.month = new_month;
            current_product->expiration_date.year = new_year;

            update_elem_in_array(repository->products_list, i, current_product);
        }
    }
    return 1;
}

/// Adds 10 products to the repository
void add_generated_products(Repository* repository)
{
    add_product_repository(repository, "Yogurt", "diary", 6, 3, 4, 2025);
    add_product_repository(repository, "Ice cream", "sweets", 100, 1, 1, 2024);
    add_product_repository(repository, "Sausage", "meat", 3, 10, 12, 2024);
    add_product_repository(repository, "Strawberry", "fruit", 12, 22, 5, 2024);
    add_product_repository(repository, "Milk", "diary", 2, 30, 10, 2025);
    add_product_repository(repository, "Chocolate", "sweets", 4, 19, 11, 2027);
    add_product_repository(repository, "Ham", "meat", 15, 27, 9, 2026);
    add_product_repository(repository, "Blueberry", "fruit", 30, 8, 3, 2028);
    add_product_repository(repository, "Banana", "fruit", 5, 31, 5, 2024);
    add_product_repository(repository, "Donut", "sweets", 20, 11, 7, 2025);
}
