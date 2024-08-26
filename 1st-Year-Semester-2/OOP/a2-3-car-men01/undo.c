#include "undo.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

Operation* create_operation(Product* product, char* operation_type)
{
    Operation* operation = malloc(sizeof(Operation));
    if (operation == NULL)
        return NULL;
    operation->product = copy_product(product);

    if (operation_type != NULL)
    {
        operation->operationType = malloc(sizeof(char) * (strlen(operation_type) + 1));
        if (operation->operationType == NULL)
        {
            free(operation);
            return NULL;
        }
        strcpy(operation->operationType, operation_type);
    }
    else
        operation->operationType = NULL;

    return operation;
}

void destroy_operation(Operation* operation)
{
    if (operation == NULL)
        return;

    // first destroy the planet
    destroy_product(operation->product);
    // then the operationType
    free(operation->operationType);
    // then free the operation
    free(operation);
}

Operation* copy_operation(Operation * operation)
{
    if (operation == NULL)
        return NULL;
    Operation* copy = create_operation(get_product(operation), get_operation_type(operation));
    return copy;
}

char* get_operation_type(Operation* operation)
{
    return operation->operationType;
}

Product* get_product(Operation* operation)
{
    return operation->product;
}

OperationsStack* create_stack()
{
    OperationsStack* stack = malloc(sizeof(OperationsStack));
    if (stack == NULL)
        return NULL;
    stack->stack = create_dynamic_array(50, (destroyFunction) &destroy_operation);
    if (stack->stack == NULL)
    {
        free(stack);
        return NULL;
    }
    return stack;
}

void destroy_stack(OperationsStack* stack)
{
    if (stack == NULL)
        return;
    // first deallocate the memory for the dynamic array
    destroy_dynamic_array(stack->stack);
    // then free the stack
    free(stack);
}

void push(OperationsStack* stack, Operation* operation)
{
    if (stack == NULL || operation == NULL)
        return;
    add_elem_to_array(stack->stack, operation);
}

Operation* pop(OperationsStack* stack)
{
    if (stack == NULL)
        return NULL;
    int last_position = get_size(stack->stack) - 1;
    Operation* operation = (Operation*)get(stack->stack, last_position); // must cast it to Operation*, as it is a void*
    // make a copy to use it for redo as well
    Operation* last_operation = copy_operation(operation);
    delete_elem_from_array(stack->stack, last_position);
    return last_operation;
}

int is_empty(OperationsStack* stack)
{
    if (stack == NULL)
        return 1;
    return (get_size(stack->stack) == 0);
}
