#pragma once
#include "domain.h"
#include "dynamic_array.h"
#include <string.h>

typedef struct
{
    Product* product;
    char* operationType;
} Operation;

Operation* create_operation(Product* product, char* operation_type);
void destroy_operation(Operation* operation);
Operation* copy_operation(Operation* operation);
char* get_operation_type(Operation* operation);
Product* get_product(Operation* operation);

typedef struct
{
    DynamicArray* stack;
} OperationsStack;

OperationsStack* create_stack();
void destroy_stack(OperationsStack* stack);
void push(OperationsStack* stack, Operation* operation);
Operation* pop(OperationsStack* stack);
int is_empty(OperationsStack* stack);

//void testsStack();