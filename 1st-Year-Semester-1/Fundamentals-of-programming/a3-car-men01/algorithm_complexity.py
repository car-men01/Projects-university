# Basic set: Bubble Sort
# Advanced set: Comb sort

import random
import copy
import timeit

menu_options = {
    1: 'Create 5 lists of random natural numbers between 0 and 100',
    2: 'Sort the first list using Bubble Sort ',
    3: 'Sort the first list using Comb Sort',
    4: 'Best case Bubble sort and Comb sort',
    5: 'Average case Bubble sort and Comb sort',
    6: 'Worst case Bubble sort and Comb sort',
    7: 'Exit the program',
}

def print_menu():
    for key in menu_options.keys():
        print(key, '~', menu_options[key])

def bubble_sort_with_step(random_list, step):
    print('The list is being sorted and the results are shown with a step of ' + str(step) + ':')
    step_counter = 0
    for i in range(0, len(random_list)):
        is_swapped = False
        for j in range(0, len(random_list)-i-1):
            if random_list[j] > random_list[j+1]:
                random_list[j], random_list[j+1] = random_list[j+1], random_list[j]
                is_swapped = True
                step_counter += 1
                if step_counter % step == 0:
                    print(str(step_counter) + ': ' + str(random_list))
        if not is_swapped:
            break
    print('Sorted list: ' + str(copy_random_list))

def comb_sort_with_step(random_list, step):
    print('The list is being sorted and the results are shown with a step of ' + str(step) + ':')
    step_counter = 0
    gap = len(random_list)
    is_sorted = False
    while not is_sorted:
        gap = int(gap / 1.3)  # 1.3 = gap shrink factor
        if gap <= 1:
            is_sorted = True
            gap = 1
        for i in range(0, len(random_list) - gap):
            if random_list[i] > random_list[gap + i]:
                random_list[i], random_list[gap + i] = random_list[gap + i], random_list[i]
                is_sorted = False
                step_counter += 1
                if step_counter % step == 0:
                    print(str(step_counter) + ': ' + str(random_list))
    print('Sorted list: ' + str(random_list))

def bubble_sort(random_list):
    for i in range(0, len(random_list)):
        is_swapped = False
        for j in range(0, len(random_list)-i-1):
            if random_list[j] > random_list[j+1]:
                random_list[j], random_list[j+1] = random_list[j+1], random_list[j]
                is_swapped = True
        if not is_swapped:
            break
    #print('Sorted list: ' + str(random_list))

def comb_sort(random_list):
    gap = len(random_list)
    is_sorted = False
    while not is_sorted:
        gap = int(gap / 1.3)  # 1.3 = gap shrink factor
        if gap <= 1:
            is_sorted = True
            gap = 1
        for i in range(0, len(random_list) - gap):
            if random_list[i] > random_list[gap + i]:
                random_list[i], random_list[gap + i] = random_list[gap + i], random_list[i]
                is_sorted = False
    #print('Sorted list: ' + str(random_list))

def execution_time_bubble_sort(random_list):
    start_timer_bubble = timeit.default_timer()
    bubble_sort(random_list)
    end_timer_bubble = timeit.default_timer()
    sorting_time_bubble = int((end_timer_bubble - start_timer_bubble) * (10 ** 7)) / (10 ** 4)  # aproximez la 4 zecimale rezultatul
    return sorting_time_bubble

def execution_time_comb_sort(random_list):
    start_timer_comb = timeit.default_timer()
    comb_sort(random_list)
    end_timer_comb = timeit.default_timer()
    sorting_time_comb = int((end_timer_comb - start_timer_comb) * (10 ** 7)) / (10 ** 4)
    return sorting_time_comb


print_menu()

def generate_random_numbers_list (list_length):
    random_list = []
    for i in range(list_length):
        random_list.append(random.randint(0, 100))
    return random_list

while True:
    option = int(input('\nEnter an option from the menu: '))
    print('')
    if option == 1:
        print('You are creating 5 lists of random natural numbers, each list having twice the number of elements of the previous one.')
        initial_list_length = int(input('Enter a number to determine the length of the first list: '))
        random_list_initial_length = generate_random_numbers_list(initial_list_length)
        random_list_initial_length_multiplied_2 = generate_random_numbers_list(initial_list_length*2)
        random_list_initial_length_multiplied_4 = generate_random_numbers_list(initial_list_length*4)
        random_list_initial_length_multiplied_8 = generate_random_numbers_list(initial_list_length*8)
        random_list_initial_length_multiplied_16 = generate_random_numbers_list(initial_list_length*16)
        print(('The 5 lists have been created, having the lengths of ' + str(initial_list_length) + ', ' +
               str(initial_list_length*2) + ', ' + str(initial_list_length*4) + ', ' + str(initial_list_length*8) +
               ' and ' + str(initial_list_length*16) + ' elements.'))

    elif option == 2:
        try:
            print('You are sorting the first list using Bubble Sort.')
            step = int(input('Enter a step: '))
            copy_random_list = copy.deepcopy(random_list_initial_length)
            bubble_sort_with_step(copy_random_list, step)
        except:
            print('Please create the lists first.')
    elif option == 3:
        try:
            print('You are sorting the first list using Comb Sort.')
            step = int(input('Enter a step: '))
            copy_random_list = copy.deepcopy(random_list_initial_length)
            comb_sort_with_step(copy_random_list, step)
        except:
            print('Please create the lists first.')
    elif option == 4:
        print("Best case scenario.")
        print(('For bubble sort and as well as for comb sort the best case scenario occurs when the list is already '
               'sorted in ascending order, meaning that there is no sorting required.\n'))
        print('In the best case scenario, the complexity for bubble sort is O(n) and for comb sort is O(nlog(n))\n')

        random_list = [
            copy.deepcopy(random_list_initial_length),
            copy.deepcopy(random_list_initial_length_multiplied_2),
            copy.deepcopy(random_list_initial_length_multiplied_4),
            copy.deepcopy(random_list_initial_length_multiplied_8),
            copy.deepcopy(random_list_initial_length_multiplied_16)
        ]
        double_list_length = 1
        for i in range(5):
            random_list[i].sort()
            print(('The list number ' + str(i+1) + ', having ' + str(initial_list_length * double_list_length) +
                   ' elements was sorted using bubble sort in ' + str(execution_time_bubble_sort(random_list[i])) +
                   ' milliseconds and using comb sort in ' + str(execution_time_comb_sort(random_list[i])) + ' milliseconds'))
            double_list_length = double_list_length * 2


    elif option == 5:
        print("Average case scenario.")
        print(('For bubble sort and as well as for comb sort the average case scenario occurs when the elements '
               'of the list are in jumbled order, meaning that they are not sorted in any way.\n'))
        print('In the average case scenario, the complexity for bubble sort and for comb sort is O(n^2)\n')
        random_list = [
            copy.deepcopy(random_list_initial_length),
            copy.deepcopy(random_list_initial_length_multiplied_2),
            copy.deepcopy(random_list_initial_length_multiplied_4),
            copy.deepcopy(random_list_initial_length_multiplied_8),
            copy.deepcopy(random_list_initial_length_multiplied_16)
        ]
        double_list_length = 1
        for i in range(5):
            print(('The list number ' + str(i+1) + ', having ' + str(initial_list_length * double_list_length) +
                   ' elements was sorted using bubble sort in ' + str(execution_time_bubble_sort(random_list[i])) +
                   ' milliseconds and using comb sort in ' + str(execution_time_comb_sort(random_list[i])) + ' milliseconds'))
            double_list_length = double_list_length * 2

    elif option == 6:
        print("Worst case scenario.")
        print(('For bubble sort and as well as for comb sort the worst case scenario occurs when the list is sorted, '
               'but in reverse order.\n'))
        print('In the worst case scenario, the complexity for bubble sort and for comb sort is O(n^2)\n')
        random_list = [
            copy.deepcopy(random_list_initial_length),
            copy.deepcopy(random_list_initial_length_multiplied_2),
            copy.deepcopy(random_list_initial_length_multiplied_4),
            copy.deepcopy(random_list_initial_length_multiplied_8),
            copy.deepcopy(random_list_initial_length_multiplied_16)
        ]
        double_list_length = 1
        for i in range(5):
            random_list[i].sort(reverse=True)
            print(('The list number ' + str(i + 1) + ', having ' + str(initial_list_length * double_list_length) +
                   ' elements was sorted using bubble sort in ' + str(execution_time_bubble_sort(random_list[i])) +
                   ' milliseconds and using comb sort in ' + str(execution_time_comb_sort(random_list[i])) + ' milliseconds'))
            double_list_length = double_list_length * 2

    elif option == 7:
        print('You exited the program, thank you!')
        exit()
    else:
        print('Invalid option, please enter a number between 1 and 7.')
