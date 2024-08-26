#pragma once
#include "domain.h"
#include "dynamic_array.h"
#include "repository.h"
#include "undo.h"

typedef struct
{
    Repository* repository;
    OperationsStack* undo_stack;
    OperationsStack* redo_stack;
} Controller;

Controller* create_controller(Repository* repository, OperationsStack* undo_stack, OperationsStack* redo_stack);
void destroy_controller(Controller* controller);

void add_product(Controller* controller, char name[], char category[], int quantity, int day, int month, int year);
void update_product(Controller* controller, char name[], char category[], int quantity, int new_day, int new_month, int new_year);
void delete_product(Controller* controller, char name[], char category[]);
void sort_ascending_by_quantity(DynamicArray* products_list);
void find_products(Controller* controller, DynamicArray* matched_products, char string_name[]);
void find_products_by_category(Controller* controller, DynamicArray* matched_products, char input_category[], int number_of_days, Date current_date);
int check_input_name_category(Controller* controller, char name[], char category[]);

int undo(Controller* controller);
int redo(Controller* controller);
