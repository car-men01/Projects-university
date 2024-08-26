#include "domain.h"
#include "dynamic_array.h"
#include "repository.h"
#include "controller.h"
#include "UI.h"
#include "undo.h"
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>

/// Intelligent refrigerator

int main() {
    Repository* repository = create_repository();
    OperationsStack* undo_stack = create_stack();
    OperationsStack* redo_stack = create_stack();
    Controller* controller = create_controller(repository, undo_stack, redo_stack);
    UI* ui = create_ui(controller);

    add_generated_products(repository);

    int option;

    while (1) {
        print_menu();
//        printf("Enter an option from the menu:");
//        scanf("%d", &option);
        option = read_integer_number("Enter an option from the menu:");
        printf("\n");

        if (option == 1) {
            add_product_ui(ui);
        }
        else if (option == 2) {
            delete_product_ui(ui);
        }
        else if (option == 3) {
            update_product_ui(ui);
        }
        else if (option == 4) {
            display_all_products(ui->controller->repository->products_list);
        }
        else if (option == 5) {
            display_by_string(ui);
        }
        else if (option == 6) {
            display_by_category(ui);
        }
        else if (option == 7) {
            int result;
            result = undo(ui->controller);
            if (result)
                printf("Undo was successful!\n\n");
            else
                printf("No more undos possible.\n\n");
        }
        else if (option == 8) {
            int result;
            result = redo(ui->controller);
            if (result)
                printf("Redo was successful!\n\n");
            else
                printf("No more redos possible.\n\n");
        }
        else if (option == 9) {
            printf("%s", "You exited the program, thank you!\n");
//            exit(0);
            break;
        }
        else
            printf("Invalid option. Please enter a number between 1 and 9.\n\n");
    }

    destroy_ui(ui);

    printf("%d",_CrtDumpMemoryLeaks());

    return 0;
}
