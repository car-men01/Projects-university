#pragma once

#include "domain.h"

typedef void* TElem;

typedef void (*destroyFunction)(TElem);

typedef struct
{
    int size, capacity;
    TElem* elems;
    destroyFunction destroyFct;
} DynamicArray;

DynamicArray* create_dynamic_array(int capacity, destroyFunction fct);
void destroy_dynamic_array(DynamicArray* arr);
void resize(DynamicArray* arr);
void add_elem_to_array(DynamicArray* arr, TElem elem);
void delete_elem_from_array(DynamicArray* arr, int index);
void update_elem_in_array(DynamicArray* arr, int index, TElem elem);
TElem get(DynamicArray* arr, int pos);
void get_elem_from_array(DynamicArray* arr, int index, TElem* elem);
void set_elem_in_array(DynamicArray* arr, int index, TElem elem);
void update_size(DynamicArray* arr, int* size);
int get_size(DynamicArray* arr);


