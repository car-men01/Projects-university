# Basic set: Bubble Sort
# Advanced set: Comb sort

import random
import copy

menu_options = {
    1: 'Create a list of n random natural numbers between 0 and 100',
    2: 'Sort the list using Bubble Sort',
    3: 'Sort the list using Comb Sort',
    4: 'Exit the program',
}

def print_menu():
    for key in menu_options.keys():
        print(key, '~', menu_options[key])

def bubble_sort(list_for_bubble_sort, step):
    print('The list is being sorted and the results are shown with a step of ' + str(step) + ':')
    step_counter = 0
    for i in range(0, len(list_for_bubble_sort)):
        is_swapped = False
        for j in range(0, len(list_for_bubble_sort)-i-1):
            if list_for_bubble_sort[j] > list_for_bubble_sort[j+1]:
                list_for_bubble_sort[j], list_for_bubble_sort[j+1] = list_for_bubble_sort[j+1], list_for_bubble_sort[j]
                is_swapped = True
                step_counter += 1
                if step_counter % step == 0:
                    print(str(step_counter) + ': ' + str(list_for_bubble_sort))
        if not is_swapped:
            break
    print('Sorted list: ' + str(list_for_bubble_sort))

def comb_sort(list_for_comb_sort, step):
    print('The list is being sorted and the results are shown with a step of ' + str(step) + ':')
    step_counter = 0
    gap = len(list_for_comb_sort)
    is_sorted = False
    while not is_sorted:
        gap = int(gap / 1.3)  # 1.3 = gap shrink factor
        if gap <= 1:
            is_sorted = True
            gap = 1
        for i in range(0, len(list_for_comb_sort) - gap):
            if list_for_comb_sort[i] > list_for_comb_sort[gap + i]:
                list_for_comb_sort[i], list_for_comb_sort[gap + i] = list_for_comb_sort[gap + i], list_for_comb_sort[i]
                is_sorted = False
                step_counter += 1
                if step_counter % step == 0:
                    print(str(step_counter) + ': ' + str(list_for_comb_sort))
    if step_counter % step != 0:
        print('Sorted list: ' + str(list_for_comb_sort))

print_menu()

while True:
    option = int(input('\nEnter an option from the menu: '))
    if option == 1:
        print('You are creating a list of n random natural numbers between 0 and 100.')
        list_length = int(input('Enter a number to determine the length of the list: n = '))
        print('Your list of ' + str(list_length) + ' numbers has been created:')
        randomlist = random.sample(range(0, 101), list_length)
        print(randomlist)
    elif option == 2:
        try:
            print('You are sorting the list using Bubble Sort.')
            step = int(input('Enter a step: '))
            list_for_bubble_sort = copy.deepcopy(randomlist)
            bubble_sort(list_for_bubble_sort, step)
        except:
            print('Please create a list first.')
    elif option == 3:
        try:
            print('You are sorting the list using Comb Sort.')
            step = int(input('Enter a step: '))
            list_for_comb_sort = copy.deepcopy(randomlist)
            comb_sort(list_for_comb_sort, step)
        except:
            print('Please create a list first.')
    elif option == 4:
        print('You exited the program, thank you!')
        exit()
    else:
        print('Invalid option, please enter a number between 1 and 4.')
