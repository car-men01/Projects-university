#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#

from ui import ui
from functions import generate_random_list_of_scores_for_10_participants, build_stack_of_last_performed_operations

if __name__ == '__main__':
    list_of_participants = generate_random_list_of_scores_for_10_participants()
    stack_of_last_performed_operations = []
    stack_of_last_performed_operations = build_stack_of_last_performed_operations(list_of_participants,
                                                                                  stack_of_last_performed_operations)
    ui(list_of_participants, stack_of_last_performed_operations)
