#include "domain.h"
#include <stdlib.h>
#include <string.h>


Product* create_product(char name[], char category[], int quantity, Date expiration_date)
{
    Product *product = malloc(sizeof(Product));
    if (product == NULL)
        return NULL;

    product->name = malloc(sizeof(char) * (strlen(name) + 1));
    if(product->name == NULL)
    {
        free(product);
        return NULL;
    }

    product->category = malloc(sizeof(char) * (strlen(category) + 1));
    if(product->category == NULL)
    {
        free(product->name);
        free(product);
        return NULL;
    }

    product->quantity = quantity;
    product->expiration_date.day = expiration_date.day;
    product->expiration_date.month = expiration_date.month;
    product->expiration_date.year = expiration_date.year;

    strcpy(product->name, name);
    strcpy(product->category, category);

    return product;
}

void destroy_product(Product* product)
{
    if(product == NULL)
        return;
    free(product->name);
    free(product->category);
    free(product);
}

Product* copy_product(Product* product)
{
    if (product == NULL)
        return NULL;
    Product* newProduct = create_product(get_name(*product), get_category(*product), get_quantity(*product), get_expiration_date(*product));
    return newProduct;
}

char* get_name(Product product)
{
    return product.name;
}

char* get_category(Product product)
{
    return product.category;
}

int get_quantity(Product product)
{
    return product.quantity;
}

Date get_expiration_date(Product product)
{
    return product.expiration_date;
}
