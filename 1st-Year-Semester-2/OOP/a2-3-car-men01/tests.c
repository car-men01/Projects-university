#include "tests.h"
#include <assert.h>

void testProduct()
{
    Date d = {1, 2, 2023};
    Product* p = create_product("Apple", "fruit", 3, d);
    assert(strcmp(get_name(*p), "Apple") == 0);
    assert(strcmp(get_category(*p), "fruit") == 0);
    assert(get_quantity(*p) == 2023);
    destroy_product(p);
}

void testDynamicArray()
{
    DynamicArray* array = create_dynamic_array(2, (destroyFunction) &destroy_product);
    Date d = {1, 2, 2023};
    Product* p = create_product("Apple", "fruit", 3, d);
    add_elem_to_array(array, p);
    assert(get_size(array) == 1);
    assert(get(array, 0) == p);
    destroy_dynamic_array(array);
}

void testStack()
{
    OperationsStack* s = create_stack();
    Date d = {1, 2, 2023};
    Product* p = create_product("Apple", "fruit", 3, d);
    Operation* o = create_operation(p, "add");
    push(s, o);
    assert(is_empty(s) == 0);
    assert(pop(s) == o);
    assert(is_empty(s) == 1);
    destroy_stack(s);
}

void testController()
{
    Repository* r = create_repository();
    OperationsStack* s_undo = create_stack();
    OperationsStack* s_redo = create_stack();
    Controller* c = create_controller(r, s_undo, s_redo);
    assert(c->repository == r);
    assert(c->undo_stack == s_undo);
    assert(c->redo_stack == s_redo);
    destroy_controller(c);
}

void testRepository()
{
    Repository* r = create_repository();
    Date d = {1, 2, 2023};
    Product* p = create_product("Apple", "fruit", 3, d);
    add_elem_to_array(r->products_list, p);
    assert(get_all_products(r) == r->products_list);
    assert(get_position_of_product(r, "Apple", "fruit") == 0);
    destroy_repository(r);
}

void testService()
{
    Repository* r = create_repository();
    OperationsStack* s_undo = create_stack();
    OperationsStack* s_redo = create_stack();
    Controller* c = create_controller(r, s_undo, s_redo);

    add_product(c, "Apple", "fruit", 3, 1, 2, 2023);
    assert(get_position_of_product(r, "Apple", "fruit") == 0);

    update_product(c, "Apple", "fruit", 4, 4, 5, 2025);
    assert(get_position_of_product(r, "Apple", "fruit") == 0);

    delete_product(c, "1", "2");
    assert(get_position_of_product(r, "Apple", "fruit") == -1);

    add_product(c, "Melon", "fruits", 15, 1, 4, 2024);
    add_product(c, "Apple Pie", "sweets", 5, 10, 9, 2024);

    DynamicArray* matched_products = create_dynamic_array(10, (destroyFunction) &destroy_product);

    find_products(c, matched_products, "pp");

    assert(get_size(matched_products) == 2);
    assert(strcmp(get_name(*(Product*)get(matched_products, 0)), "Apple") == 0);
    assert(strcmp(get_name(*(Product*)get(matched_products, 1)), "Apple Pie") == 0);

    find_products_by_category(c, matched_products, "fruits", 30, (Date){2024, 4, 1});

    assert(get_size(matched_products) == 1);
    assert(strcmp(get_name(*(Product*)get(matched_products, 0)), "Apple") == 0);

    destroy_dynamic_array(matched_products);
    destroy_controller(c);
}

void testAll()
{
    testProduct();
    testDynamicArray();
    testStack();
    testController();
    testRepository();
    testService();
}
