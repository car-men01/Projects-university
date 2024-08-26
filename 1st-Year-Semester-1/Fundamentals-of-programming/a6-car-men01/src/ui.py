#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements)
# are found here
#

from functions import *

# list
def display_participants_all_scores(list_of_participants: list):
    for i in range(len(list_of_participants)):
        print(f"Participant {i+1} - P1 score: {get_participant_score_1(list_of_participants[i])}, P2 score: "
              f"{get_participant_score_2(list_of_participants[i])}, P3 score:"
              f" {get_participant_score_3(list_of_participants[i])}")

def display_list_of_sorted_participants(list_of_participants: list):
    sorted_list_of_participants, participant_index_list = sort_list_of_participants_descending(list_of_participants)
    for i in range(len(sorted_list_of_participants)):
        print(f"Participant {int(participant_index_list[i]) + 1} - P1 score: "
              f"{get_participant_score_1(sorted_list_of_participants[i])}, P2 score: "
              f"{get_participant_score_2(sorted_list_of_participants[i])}, P3 score:"
              f" {get_participant_score_3(sorted_list_of_participants[i])}")

def display_list_of_participant_compared_scores(list_of_participants: list, list_of_average_scores: list):
    for i in range(len(list_of_average_scores)):
        print(f"Participant {list_of_average_scores[i] + 1} - P1 score: "
              f"{get_participant_score_1(list_of_participants[list_of_average_scores[i]])}, P2 score: "
              f"{get_participant_score_2(list_of_participants[list_of_average_scores[i]])}, P3 score:"
              f" {get_participant_score_3(list_of_participants[list_of_average_scores[i]])}")

def display_top_participants_average_score(list_of_participants: list, number_of_participants: int):
    sorted_list_of_participants, participant_index_list = sort_list_of_participants_descending(list_of_participants)
    for i in range(number_of_participants):
        print(f"Participant {int(participant_index_list[i]) + 1} - P1 score: "
              f"{get_participant_score_1(sorted_list_of_participants[i])}, P2 score: "
              f"{get_participant_score_2(sorted_list_of_participants[i])}, P3 score:"
              f" {get_participant_score_3(sorted_list_of_participants[i])}")

def display_top_participants_one_problem_score(list_of_participants: list, number_of_participants: int,
                                               problem_number: str):
    if problem_number == 'P1':
        problem_number = 0
    elif problem_number == 'P2':
        problem_number = 1
    elif problem_number == 'P3':
        problem_number = 2
    sorted_list_of_participants, participant_index_list = (sort_list_of_participants_one_problem_score
                                                           (list_of_participants, problem_number))
    for i in range(number_of_participants):
        print(f"Participant {int(participant_index_list[i]) + 1} - P1 score: "
              f"{get_participant_score_1(sorted_list_of_participants[i])}, P2 score: "
              f"{get_participant_score_2(sorted_list_of_participants[i])}, P3 score:"
              f" {get_participant_score_3(sorted_list_of_participants[i])}")

def ui(list_of_participants, stack_of_last_performed_operations):
    while True:
        user_command = input("\nEnter your command here >>> ")
        user_input_list = user_command.split(" ")
        print("")
        try:
            if user_input_list[0] == "add" and len(user_input_list) == 4:  # 0 - position of the add command
                                                                           # 4 - len of add command and 3 input scores
                try:
                    # 1, 2, 3 - the positions of the participants scores
                    if test_participants_scores(int(user_input_list[1]), int(user_input_list[2]),
                                                int(user_input_list[3])):
                        list_of_participants = add_scores_new_participant(list_of_participants, int(user_input_list[1]),
                                                                          int(user_input_list[2]),
                                                                          int(user_input_list[3]))
                        stack_of_last_performed_operations = build_stack_of_last_performed_operations(
                            list_of_participants, stack_of_last_performed_operations)
                        display_participants_all_scores(list_of_participants)
                    else:
                        print("The 3 scores can be minimum 0 and maximum 10.")
                except (ValueError, IndexError):
                    print("Please provide 3 relevant scores for the participant.")

            elif user_input_list[0] == "insert" and user_input_list[4] == "at":  # 0, 4 - position of the insert...to command
                try:
                    # 1, 2, 3 - position of the participants scores, 5 - position of the participant
                    if (test_participants_scores(int(user_input_list[1]), int(user_input_list[2]),
                                                 int(user_input_list[3]))
                            and test_participant_position(list_of_participants, int(user_input_list[5]))):
                        list_of_participants = insert_scores_new_participant_at_given_position(list_of_participants,
                                                                                               int(user_input_list[1]),
                                                                                               int(user_input_list[2]),
                                                                                               int(user_input_list[3]),
                                                                                               int(user_input_list[5]))
                        stack_of_last_performed_operations = build_stack_of_last_performed_operations(
                            list_of_participants, stack_of_last_performed_operations)
                        display_participants_all_scores(list_of_participants)
                    else:
                        print(f"The 3 scores can be minimum 0 and maximum 10 and the position should be minimum 1 and "
                              f"maximum {int(len(list_of_participants))}.")
                except (ValueError, IndexError):
                    print("Please provide 3 relevant scores and one position for the participant.")

            elif user_input_list[0] == "remove":  # 0 - position of the remove command
                if len(user_input_list) == 2:  # 2 - len of remove command and participant index
                    try:
                        if test_participant_position(list_of_participants, int(user_input_list[1])):
                            list_of_participants = remove_scores_one_participant(list_of_participants,
                                                                                 int(user_input_list[1]))
                            stack_of_last_performed_operations = build_stack_of_last_performed_operations(
                                list_of_participants, stack_of_last_performed_operations)
                            display_participants_all_scores(list_of_participants)
                        else:
                            print(f"The position should be minimum 1 and maximum {int(len(list_of_participants))}.")
                    except (ValueError, IndexError):
                        print(
                            f"Please provide a relevant position from the interval: [1, {len(list_of_participants)}].")

                elif len(user_input_list) == 4:  # 4 - len of the remove...to command and 2 participants index
                    try:
                        # 1 and 3 - positions of the participants
                        if (user_input_list[2] == "to" and test_participant_position(list_of_participants,
                                                                                     int(user_input_list[1]))
                                and test_participant_position(list_of_participants, int(user_input_list[3]))):
                            if user_input_list[1] >= user_input_list[3]:  # 1 and 3 - positions of the participants
                                print("Your starting position cannot be greater than or equal to your ending position.")
                            else:
                                # 1 and 3 - positions of the participants
                                list_of_participants = remove_scores_participants(list_of_participants,
                                                                                  int(user_input_list[1]),
                                                                                  int(user_input_list[3]))
                                stack_of_last_performed_operations = build_stack_of_last_performed_operations(
                                    list_of_participants, stack_of_last_performed_operations)
                                display_participants_all_scores(list_of_participants)
                        else:
                            print(f"The two positions should be minimum 1 and maximum "
                                  f"{int(len(list_of_participants))}.")
                    except (ValueError, IndexError):
                        print(f"Please provide two relevant positions from the interval: "
                              f"[1, {len(list_of_participants)}].")

                elif user_input_list[1] == "=":  # 1 - position of the '=' sign
                    try:
                        # 2 - position of the participant average score
                        if test_participants_input_score(int(user_input_list[2])):
                            if not list_participants_score_equal_to_given_number(list_of_participants,
                                                                                 int(user_input_list[2])):
                                print(f"There are no participants with an average score equal to "
                                      f"{int(user_input_list[2])}.")
                            else:
                                # 2 - position of the participant average score
                                remove_score_all_participants_average_score_equal_to_input(list_of_participants,
                                                                                           int(user_input_list[2]))
                                stack_of_last_performed_operations = build_stack_of_last_performed_operations(
                                    list_of_participants, stack_of_last_performed_operations)
                                display_participants_all_scores(list_of_participants)
                        else:
                            print("The input average score can be minimum 0 and maximum 10.")
                    except (ValueError, IndexError):
                        print("Please provide one relevant average score for the participants.")

                elif user_input_list[1] == ">":  # 1 - position of the '>' sign
                    try:
                        # 2 - position of the participant average score
                        if test_participants_input_score(int(user_input_list[2])):
                            if not list_participants_score_greater_than_given_number(list_of_participants,
                                                                                     int(user_input_list[2])):
                                print(f"There are no participants with an average score greater than "
                                      f"{int(user_input_list[2])}.")
                            else:
                                # 2 - position of the participant average score
                                remove_score_all_participants_average_score_greater_than_input(list_of_participants,
                                                                                               int(user_input_list[2]))
                                stack_of_last_performed_operations = build_stack_of_last_performed_operations(
                                    list_of_participants, stack_of_last_performed_operations)
                                display_participants_all_scores(list_of_participants)
                        else:
                            print("The input average score can be minimum 0 and maximum 10.")
                    except (ValueError, IndexError):
                        print("Please provide one relevant average score for the participants.")

                elif user_input_list[1] == "<":  # 1 - position of the '<' sign
                    try:
                        # 2 - position of the participant average score
                        if test_participants_input_score(int(user_input_list[2])):
                            if not list_participants_score_smaller_than_given_number(list_of_participants,
                                                                                     int(user_input_list[2])):
                                print(f"There are no participants with an average score smaller than "
                                      f"{int(user_input_list[2])}.")
                            else:
                                # 2 - position of the participant average score
                                remove_score_all_participants_average_score_smaller_than_input(list_of_participants,
                                                                                               int(user_input_list[2]))
                                stack_of_last_performed_operations = build_stack_of_last_performed_operations(
                                    list_of_participants, stack_of_last_performed_operations)
                                display_participants_all_scores(list_of_participants)
                        else:
                            print("The input average score can be minimum 0 and maximum 10.")
                    except (ValueError, IndexError):
                        print("Please provide one relevant average score for the participants.")

                else:
                    print("Invalid input.")

            # 0 and 3 - position of the replace with command
            elif user_input_list[0] == "replace" and user_input_list[3] == "with":
                try:
                    # 1 - participant's position, 4 - position of the score to replace
                    if (test_participant_position(list_of_participants, int(user_input_list[1])) and
                            test_participants_input_score(int(user_input_list[4]))):
                        # 2 - position of the problem number
                        if user_input_list[2] == 'P1' or user_input_list[2] == 'P2' or user_input_list[2] == 'P3':
                            # 1 - position of the participant, 4 - position of the new score being replaced
                            list_of_participants = replace_old_scores_new_scores(list_of_participants,
                                                                                 int(user_input_list[1]),
                                                                                 user_input_list[2],
                                                                                 int(user_input_list[4]))
                            stack_of_last_performed_operations = build_stack_of_last_performed_operations(
                                list_of_participants, stack_of_last_performed_operations)
                            display_participants_all_scores(list_of_participants)
                        else:
                            print("The problem number should be stated as: P1, P2 or P3.")
                    else:
                        print(f"The participant number should be minimum 1 and maximum {int(len(list_of_participants))}"
                              f" and the input score should be minimum 0 and maximum 10.")
                except (ValueError, IndexError):
                    print("Please provide one relevant participant number, one problem number(P1, P2, P3) and one "
                          "score from the interval [1, 10].")

            elif user_input_list[0] == "list":  # 0 - position of the list command
                if len(user_input_list) == 1:  # 1 - length of the list command
                    display_participants_all_scores(list_of_participants)
                elif user_input_list[1] == "sorted":  # 1 - position of the sorted command
                    display_list_of_sorted_participants(list_of_participants)
                elif user_input_list[1] == "=":
                    try:
                        # 2 - position of the participants average score
                        if test_participants_input_score(int(user_input_list[2])):
                            if not list_participants_score_equal_to_given_number(list_of_participants,
                                                                                 int(user_input_list[2])):
                                print(f"There are no participants with an average score equal to "
                                      f"{int(user_input_list[2])}.")
                            else:
                                # 2 - position of the participants average score
                                (display_list_of_participant_compared_scores
                                    (list_of_participants, list_participants_score_equal_to_given_number
                                        (list_of_participants, int(user_input_list[2]))))
                        else:
                            print("The input average score can be minimum 0 and maximum 10.")
                    except (ValueError, IndexError):
                        print("Please provide one relevant average score for the participants.")

                elif user_input_list[1] == ">":  # 1 - position of the '>' sign
                    try:
                        # 2 - position of the participants average score
                        if test_participants_input_score(int(user_input_list[2])):
                            if not list_participants_score_greater_than_given_number(list_of_participants,
                                                                                     int(user_input_list[2])):
                                print(f"There are no participants with an average score greater than "
                                      f"{int(user_input_list[2])}.")
                            else:
                                # 2 - position of the participants average score
                                (display_list_of_participant_compared_scores
                                    (list_of_participants, list_participants_score_greater_than_given_number
                                        (list_of_participants, int(user_input_list[2]))))
                        else:
                            print("The input average score can be minimum 0 and maximum 10.")
                    except (ValueError, IndexError):
                        print("Please provide one relevant average score for the participants.")

                elif user_input_list[1] == "<":  # 1 - position of the '<' sign
                    try:
                        # 2 - position of the participants average score
                        if test_participants_input_score(int(user_input_list[2])):
                            if not list_participants_score_smaller_than_given_number(list_of_participants,
                                                                                     int(user_input_list[2])):
                                print(f"There are no participants with an average score smaller than "
                                      f"{int(user_input_list[2])}.")
                            else:
                                # 2 - position of the participants average score
                                (display_list_of_participant_compared_scores
                                    (list_of_participants, list_participants_score_smaller_than_given_number
                                        (list_of_participants, int(user_input_list[2]))))
                        else:
                            print("The input average score can be minimum 0 and maximum 10.")
                    except (ValueError, IndexError):
                        print("Please provide one relevant average score for the participants.")

                else:
                    print("Invalid input.")

            elif user_input_list[0] == "top":  # 0 - position of the top command
                if len(user_input_list) == 2:  # 2 - len of the top command and number of participants
                    try:
                        # 1 - position of the number of participants to display
                        if test_participant_position(list_of_participants, int(user_input_list[1])):
                            display_top_participants_average_score(list_of_participants, int(user_input_list[1]))
                        else:
                            print(f"The number of top participants to be displayed can be minimum 1 and maximum "
                                  f"{int(len(list_of_participants))}.")
                    except (ValueError, IndexError):
                        print("Please provide a relevant number of scores for the participants.")

                elif len(user_input_list) == 3:  # 3 - len of the top command,problem number and number of participants
                    try:
                        # 1 - position of the number of participants to display
                        if test_participant_position(list_of_participants, int(user_input_list[1])):
                            # 2 - position of the problem number
                            if user_input_list[2] == 'P1' or user_input_list[2] == 'P2' or user_input_list[2] == 'P3':
                                display_top_participants_one_problem_score(list_of_participants,
                                                                           int(user_input_list[1]), user_input_list[2])
                            else:
                                print("The problem number should be stated as: P1, P2 or P3.")
                        else:
                            print(f"The number of top participants to be displayed can be minimum 1 and maximum "
                                  f"{int(len(list_of_participants))}.")
                    except (ValueError, IndexError):
                        print("Please provide a relevant number of scores for the participants.")

            elif user_input_list[0] == "undo":  # 0 - position of the undo command
                if len(stack_of_last_performed_operations) > 1:  # 1 - len of the stack of last performed operations
                    print("Last operation was reversed successfully\n")
                    display_participants_all_scores(undo_last_performed_operation(stack_of_last_performed_operations))
                else:
                    print("There is no operation left to reverse.")

            else:
                print("Your command was not typed in properly. Please try one of the following commands:\n"
                      "(A) add <P1 score> <P2 score> <P3 score>, insert <P1 score> <P2 score> <P3 score> at "
                      "<position>\n(B) remove <position>, remove <start position> to <end position>, replace "
                      "<old score> <P1 | P2 | P3> with <new score>\n(C) list, list sorted, list [ < | = | > ] "
                      "<score>\n(D) top <number>, top <number> <P1 | P2 | P3>, remove [ < | = | > ] <score>\n"
                      "(E) undo")

        except (ValueError, IndexError):
            print("Your command was not typed in properly. Please try one of the following commands:\n"
                  "(A) add <P1 score> <P2 score> <P3 score>, insert <P1 score> <P2 score> <P3 score> at "
                  "<position>\n(B) remove <position>, remove <start position> to <end position>, replace "
                  "<old score> <P1 | P2 | P3> with <new score>\n(C) list, list sorted, list [ < | = | > ] "
                  "<score>\n(D) top <number>, top <number> <P1 | P2 | P3>, remove [ < | = | > ] <score>\n"
                  "(E) undo")
