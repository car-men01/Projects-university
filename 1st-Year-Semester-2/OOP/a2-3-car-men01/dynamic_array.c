#include "dynamic_array.h"
#include <stdlib.h>

DynamicArray* create_dynamic_array(int capacity, destroyFunction fct)
{
    DynamicArray* arr = malloc(sizeof(DynamicArray));
    if (arr == NULL)
        return NULL;
    arr->capacity = capacity;
    arr->size = 0;
    arr->elems = malloc(sizeof(TElem) * capacity);
    if (arr->elems == NULL)
    {
        free(arr);
        return NULL;
    }
    arr->destroyFct = fct;
    return arr;
}

void destroy_dynamic_array(DynamicArray* arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; i < arr->size; i++)
        arr->destroyFct(arr->elems[i]);
    free(arr->elems);
    free(arr);
}

void resize(DynamicArray* arr)
{
    if (arr == NULL)
        return;
    arr->capacity *= 2;
    TElem* aux = realloc(arr->elems, sizeof(TElem) * arr->capacity);
    if (aux == NULL)
        return;
    arr->elems = aux;
}

void add_elem_to_array(DynamicArray* arr, TElem elem)
{
    if (arr == NULL)
        return;
    if (arr->size == arr->capacity)
        resize(arr);
    arr->elems[arr->size++] = elem;
}

void delete_elem_from_array(DynamicArray* arr, int index)
{
    if (arr == NULL)
        return;
    if (index < 0 || index >= arr->size)
        return;
    arr->destroyFct(arr->elems[index]);
    for (int i = index; i < arr->size - 1; i++)
        arr->elems[i] = arr->elems[i + 1];
    arr->size--;
}

void update_elem_in_array(DynamicArray* arr, int index, TElem elem)
{
    if (arr == NULL)
        return;
    if (index < 0 || index >= arr->size)
        return;
//    arr->destroyFct(arr->elems[index]);
    arr->elems[index] = elem;
}

void get_all_elems(DynamicArray* arr, TElem* elems)
{
    if (arr == NULL)
        return;
    for (int i = 0; i < arr->size; i++)
        elems[i] = arr->elems[i];
}

TElem get(DynamicArray* arr, int pos)
{
    if (arr == NULL)
        return NULL;
    if (pos < 0 || pos >= arr->size)
        return NULL;
    return arr->elems[pos];
}

void get_elem_from_array(DynamicArray* arr, int index, TElem* elem)
{
    if (arr == NULL)
        return;
    if (index < 0 || index >= arr->size)
        return;
    *elem = arr->elems[index];
}

void set_elem_in_array(DynamicArray* arr, int index, TElem elem)
{
    if (arr == NULL)
        return;
    if (index < 0 || index >= arr->size)
        return;
    arr->elems[index] = elem;
}

void update_size(DynamicArray* arr, int* size)
{
    if (arr == NULL)
        return;
    *size = arr->size;
}

int get_size(DynamicArray* arr)
{
    if (arr == NULL)
        return -1;
    return arr->size;
}
