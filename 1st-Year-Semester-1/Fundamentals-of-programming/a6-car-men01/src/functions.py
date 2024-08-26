#
# The program's functions are implemented here. There is no user interaction in this file, therefore no
# input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#

# 2. Contest

import copy
from random import randint


def create_participant_with_3_scores(score1: int, score2: int, score3: int) -> list:
    return [score1, score2, score3]

def get_participant_all_scores(participant: list) -> tuple:
    return participant[0], participant[1], participant[2]

def get_participant_score_1(participant: list) -> tuple:
    return participant[0]

def get_participant_score_2(participant: list) -> tuple:
    return participant[1]

def get_participant_score_3(participant: list) -> tuple:
    return participant[2]

def set_participant_all_scores(participant: list, value_of_all_scores: int) -> tuple:
    participant[0], participant[1], participant[2] = value_of_all_scores, value_of_all_scores, value_of_all_scores
    return value_of_all_scores, value_of_all_scores, value_of_all_scores

def set_participant_one_score(participant: list, score_index: int, new_score_value: int) -> int:
    list_of_scores = list(participant)
    list_of_scores[score_index] = new_score_value
    return new_score_value

def test_participants_scores(score1: int, score2: int, score3: int) -> bool:
    if score1 < 0 or score1 > 10 or score2 < 0 or score2 > 10 or score3 < 0 or score3 > 10:
        return False
    return True

def test_participants_input_score(score: int) -> bool:
    if score < 0 or score > 10:
        return False
    return True

def test_participant_position(list_of_participants: list, position: int) -> bool:
    if position < 1 or position > len(list_of_participants):
        return False
    return True

def generate_random_list_of_scores_for_10_participants() -> list:
    list_of_participants = []
    for i in range(10):
        score1 = randint(0, 10)
        score2 = randint(0, 10)
        score3 = randint(0, 10)
        list_of_participants.append(create_participant_with_3_scores(score1, score2, score3))
    return list_of_participants

# A
# add <P1 score> <P2 score> <P3 score>
def add_scores_new_participant(list_of_participants: list, new_score1: int, new_score2: int, new_score3: int) -> list:
    list_of_participants.append(create_participant_with_3_scores(new_score1, new_score2, new_score3))
    return list_of_participants

# insert <P1 score> <P2 score> <P3 score> at <position>
def insert_scores_new_participant_at_given_position(list_of_participants: list, new_score1: int, new_score2: int,
                                                    new_score3: int, position: int) -> list:
    list_of_participants.insert(position - 1, create_participant_with_3_scores(new_score1, new_score2, new_score3))
    return list_of_participants

# B
# remove <position>
def remove_scores_one_participant(list_of_participants: list, participant_index: int) -> list:
    list_of_participants[participant_index - 1] = (set_participant_all_scores
                                                   (list_of_participants[participant_index - 1], 0))
    return list_of_participants

# remove <start position> to <end position>
def remove_scores_participants(list_of_participants: list, participant_starting_index: int,
                               participant_ending_index: int) -> list:
    for i in range(participant_starting_index - 1, participant_ending_index):
        if get_participant_all_scores(list_of_participants[i]) != (0, 0, 0):
            list_of_participants[i] = set_participant_all_scores(list_of_participants[i], 0)
    return list_of_participants

# replace <old score> <P1 | P2 | P3> with <new score>
def replace_old_scores_new_scores(list_of_participants: list, participant_index: int, problem_number: str,
                                  new_score_value: int) -> list:
    participant_index = participant_index - 1
    problem_number_int = 0
    if problem_number == 'P1':
        problem_number_int = 0
    elif problem_number == 'P2':
        problem_number_int = 1
    elif problem_number == 'P3':
        problem_number_int = 2
    list_of_scores = list(list_of_participants[participant_index])
    list_of_scores[problem_number_int] = (set_participant_one_score(list_of_participants[participant_index],
                                                                    problem_number_int, new_score_value))
    list_of_participants[participant_index] = tuple(list_of_scores)
    return list_of_participants

# C
# list sorted - display participants sorted in decreasing order of average score
def calculate_average_score_participant(participant: list) -> int:
    average_score = int(get_participant_score_1(participant) + get_participant_score_2(participant) +
                        get_participant_score_3(participant)) // 3
    return average_score

def sort_list_of_participants_descending(list_of_participants: list) -> tuple:
    sorted_list_of_participants = copy.deepcopy(list_of_participants)
    participant_index_list = []
    for i in range(len(list_of_participants)):
        participant_index_list.append(i)
    for i in range(len(sorted_list_of_participants)):
        for j in range(i+1, len(sorted_list_of_participants)):
            if (calculate_average_score_participant(sorted_list_of_participants[i]) <
                    calculate_average_score_participant(sorted_list_of_participants[j])):
                sorted_list_of_participants[i], sorted_list_of_participants[j] = (
                    sorted_list_of_participants[j], sorted_list_of_participants[i])
                participant_index_list[i], participant_index_list[j] = (participant_index_list[j],
                                                                        participant_index_list[i])
    return sorted_list_of_participants, participant_index_list

# list =
def list_participants_score_equal_to_given_number(list_of_participants: list, input_number: int) -> list:
    list_participants_average_scores_equal_to_input = []
    for i in range(len(list_of_participants)):
        if calculate_average_score_participant(list_of_participants[i]) == input_number:
            list_participants_average_scores_equal_to_input.append(i)
    return list_participants_average_scores_equal_to_input

# list >
def list_participants_score_greater_than_given_number(list_of_participants: list, input_number: int) -> list:
    list_participants_average_scores_greater_than_input = []
    for i in range(len(list_of_participants)):
        if calculate_average_score_participant(list_of_participants[i]) > input_number:
            list_participants_average_scores_greater_than_input.append(i)
    return list_participants_average_scores_greater_than_input

# list <
def list_participants_score_smaller_than_given_number(list_of_participants: list, input_number: int) -> list:
    list_participants_average_scores_smaller_than_input = []
    for i in range(len(list_of_participants)):
        if calculate_average_score_participant(list_of_participants[i]) < input_number:
            list_participants_average_scores_smaller_than_input.append(i)
    return list_participants_average_scores_smaller_than_input

# top <number> <P1 | P2 | P3>
def sort_list_of_participants_one_problem_score(list_of_participants: list, problem_number: int) -> tuple:
    sorted_list_of_participants_one_problem = copy.deepcopy(list_of_participants)
    participant_index_list = []
    for i in range(len(list_of_participants)):
        participant_index_list.append(i)
    for i in range(len(sorted_list_of_participants_one_problem)):
        for j in range(i + 1, len(sorted_list_of_participants_one_problem)):
            if (sorted_list_of_participants_one_problem[i][problem_number] <
                    sorted_list_of_participants_one_problem[j][problem_number]):
                sorted_list_of_participants_one_problem[i], sorted_list_of_participants_one_problem[j] = (
                    sorted_list_of_participants_one_problem[j], sorted_list_of_participants_one_problem[i])
                participant_index_list[i], participant_index_list[j] = (participant_index_list[j],
                                                                        participant_index_list[i])
    return sorted_list_of_participants_one_problem, participant_index_list

# remove = <score>
def remove_score_all_participants_average_score_equal_to_input(list_of_participants: list, input_average_score: int):
    for i in range(len(list_of_participants)):
        if (calculate_average_score_participant(list_of_participants[i]) == input_average_score and
                calculate_average_score_participant(list_of_participants[i]) != 0):
            list_of_participants[i] = set_participant_all_scores(list_of_participants[i], 0)

# remove > <score>
def remove_score_all_participants_average_score_greater_than_input(list_of_participants: list,
                                                                   input_average_score: int):
    for i in range(len(list_of_participants)):
        if (calculate_average_score_participant(list_of_participants[i]) > input_average_score and
                calculate_average_score_participant(list_of_participants[i]) != 0):
            list_of_participants[i] = set_participant_all_scores(list_of_participants[i], 0)

# remove < <score>
def remove_score_all_participants_average_score_smaller_than_input(list_of_participants: list,
                                                                   input_average_score: int):
    for i in range(len(list_of_participants)):
        if (calculate_average_score_participant(list_of_participants[i]) < input_average_score and
                calculate_average_score_participant(list_of_participants[i]) != 0):
            list_of_participants[i] = set_participant_all_scores(list_of_participants[i], 0)

# undo
def build_stack_of_last_performed_operations(list_of_participants: list, stack_of_last_performed_operations: list) \
        -> list:
    copy_list_of_participants = copy.deepcopy(list_of_participants)
    stack_of_last_performed_operations.append(copy_list_of_participants)
    return stack_of_last_performed_operations

def undo_last_performed_operation(stack_of_last_performed_operations: list) -> list:
    stack_of_last_performed_operations.pop()
    return stack_of_last_performed_operations[len(stack_of_last_performed_operations) - 1]
