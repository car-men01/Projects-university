#pragma once
#include "domain.h"
#include "dynamic_array.h"
#include "controller.h"
#include "undo.h"
#include "repository.h"

typedef struct
{
    Controller* controller;
} UI;

UI* create_ui(Controller* controller);
void destroy_ui(UI* ui);

int read_integer_number(const char* message);
void print_menu();
void add_product_ui(UI* ui);
void delete_product_ui(UI* ui);
void update_product_ui(UI* ui);
void display_all_products(DynamicArray* products_list);
void display_by_string(UI* ui);
void display_by_category(UI* ui);
