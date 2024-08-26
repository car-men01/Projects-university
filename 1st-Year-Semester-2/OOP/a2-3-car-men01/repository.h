#pragma once
#include "domain.h"
#include "dynamic_array.h"

typedef struct
{
    DynamicArray* products_list;
} Repository;

Repository* create_repository();
void destroy_repository(Repository* repository);
DynamicArray* get_all_products(Repository* repository);
int get_position_of_product(Repository* repository, char name[], char category[]);

int add_product_repository(Repository* repository, char name[], char category[], int quantity, int day, int month, int year);
int delete_product_repository(Repository* repository, char name[], char category[]);
int update_product_repository(Repository* repository, char name[], char category[], int new_quantity, int day, int month, int year);
void add_generated_products(Repository* repository);
