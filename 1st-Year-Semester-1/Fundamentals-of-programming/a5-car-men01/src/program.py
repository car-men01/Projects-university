#
# Write the implementation for A5 in this file
#

from random import randint

#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

"""
def create_complex_number(real_part: int, imaginary_part: int) -> list:
    # creates a complex number with the given real and imaginary parts
    return [real_part, imaginary_part]

def get_complex_number_real_part(complex_number: list) -> tuple:
    # returns the real part of a complex number as a tuple
    return complex_number[0]

def get_complex_number_imaginary_part(complex_number: list) -> tuple:
    # returns the imaginary part of a complex number as a tuple
    return complex_number[1]

def set_complex_number_real_part(complex_number: list, real_part: int) -> int:
    # sets the complex number's real part and returns it
    complex_number[0] = real_part
    return real_part

def set_complex_number_imaginary_part(complex_number: list, imaginary_part: int) -> int:
    # sets the complex number's imaginary part and returns it
    complex_number[1] = imaginary_part
    return imaginary_part

def to_str(complex_number: list) -> str:
    # returns the complex number as it's string representation
    real_part = get_complex_number_real_part(complex_number)
    imaginary_part = get_complex_number_imaginary_part(complex_number)
    if imaginary_part < 0:
        imaginary_part = str(imaginary_part)
        imaginary_part = imaginary_part[:1] + " " + imaginary_part[1:]
        return str(real_part) + " " + str(imaginary_part) + "i"
    else:
        return str(real_part) + " + " + str(imaginary_part) + "i"
"""

#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def create_complex_number(real_part: int, imaginary_part: int) -> dict:
    # creates a complex number with the given real and imaginary parts
    return {"a": real_part, "b": imaginary_part}

def get_complex_number_real_part(complex_number: dict) -> tuple:
    # returns the real part of a complex number as a tuple
    return complex_number["a"]

def get_complex_number_imaginary_part(complex_number: dict) -> tuple:
    # returns the imaginary part of a complex number as a tuple
    return complex_number["b"]

def set_complex_number_real_part(complex_number: dict, real_part: int) -> int:
    # sets the complex number's real part and returns it
    complex_number["a"] = real_part
    return real_part

def set_complex_number_imaginary_part(complex_number: dict, imaginary_part: int) -> int:
    # sets the complex number's imaginary part and returns it
    complex_number["b"] = imaginary_part
    return imaginary_part

def to_str(complex_number: dict) -> str:
    # returns the complex number as it's string representation
    real_part = get_complex_number_real_part(complex_number)
    imaginary_part = get_complex_number_imaginary_part(complex_number)
    if imaginary_part < 0:
        imaginary_part = str(imaginary_part)
        imaginary_part = imaginary_part[:1] + " " + imaginary_part[1:]
        return str(real_part) + " " + str(imaginary_part) + "i"
    else:
        return str(real_part) + " + " + str(imaginary_part) + "i"


#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def generate_random_list_of_complex_numbers() -> list:
    # generates 10 random complex numbers and returns them as a list
    list_of_random_complex_numbers = []
    for _ in range(10):
        # i chose the complex numbers to have their real nand imaginary parts in the interval [-25, 25]
        real_part = randint(-25, 25)
        imaginary_part = randint(-25, 25)
        list_of_random_complex_numbers.append(create_complex_number(real_part, imaginary_part))
    return list_of_random_complex_numbers


# 4. (naive) Length and elements of a longest subarray of numbers that contain at most 3 distinct values.

def longest_subarray_3_distinct_values(list_of_complex_numbers: list):
    maximum_subarray_length = 1
    current_subarray_length = 1
    longest_subarray_starting_index = 0
    i = 1
    # we initialize the distinct values variables with the first element from the array
    distinct_value_real_1 = get_complex_number_real_part(list_of_complex_numbers[0])
    distinct_value_imaginary_1 = get_complex_number_imaginary_part(list_of_complex_numbers[0])
    # we initialize the other distinct values with float('-inf')
    distinct_value_real_2, distinct_value_imaginary_2, distinct_value_real_3, distinct_value_imaginary_3 \
        = float('-inf'), float('-inf'), float('-inf'), float('-inf')

    while i < len(list_of_complex_numbers):
        real_part_current = get_complex_number_real_part(list_of_complex_numbers[i])
        imaginary_part_current = get_complex_number_imaginary_part(list_of_complex_numbers[i])

        # check if the current complex nr is equal to any of the other 3 distinct numbers
        if ((real_part_current == distinct_value_real_1 and imaginary_part_current == distinct_value_imaginary_1) or
                (real_part_current == distinct_value_real_2 and imaginary_part_current == distinct_value_imaginary_2) or
                (real_part_current == distinct_value_real_3 and imaginary_part_current == distinct_value_imaginary_3)):
            current_subarray_length += 1
            i += 1
        else:
            if distinct_value_real_2 == float('-inf'):
                distinct_value_real_2, distinct_value_imaginary_2 = real_part_current, imaginary_part_current
                current_subarray_length += 1
                i += 1
            elif distinct_value_real_3 == float('-inf'):
                distinct_value_real_3, distinct_value_imaginary_3 = real_part_current, imaginary_part_current
                current_subarray_length += 1
                i += 1
            else:
                if current_subarray_length > maximum_subarray_length:
                    maximum_subarray_length = current_subarray_length
                    longest_subarray_starting_index = i - current_subarray_length

                distinct_value_real_1, distinct_value_imaginary_1 = distinct_value_real_2, distinct_value_imaginary_2
                distinct_value_real_2, distinct_value_imaginary_2 = distinct_value_real_3, distinct_value_imaginary_3
                distinct_value_real_3, distinct_value_imaginary_3 = float('-inf'), float('-inf')
                current_subarray_length = 2

    if current_subarray_length > maximum_subarray_length:
        maximum_subarray_length = current_subarray_length
        longest_subarray_starting_index = i - current_subarray_length

    return longest_subarray_starting_index, maximum_subarray_length


# 11. (dp) The length and elements of a maximum subarray sum, when considering each number's real part.

def maximum_subarray_sum_real_parts(list_of_complex_numbers: list):
    maximum_sum = float('-inf')
    current_sum = 0
    maximum_sum_starting_index = 0
    maximum_sum_ending_index = 0
    current_subarray_starting_index = 0

    for i in range(len(list_of_complex_numbers)):
        real_part = int(get_complex_number_real_part(list_of_complex_numbers[i]))
        current_sum = max(real_part, current_sum + real_part)
        if current_sum == real_part:
            current_subarray_starting_index = i
        if current_sum > maximum_sum:
            maximum_sum = current_sum
            maximum_sum_starting_index, maximum_sum_ending_index = current_subarray_starting_index, i

    return maximum_sum, maximum_sum_starting_index, maximum_sum_ending_index

#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def read_complex_numbers() -> list:
    number_of_complex_numbers = int(input("Enter how many complex numbers you want to create: "))
    list_of_complex_numbers = []
    counter_complex_number = 1
    while counter_complex_number <= number_of_complex_numbers:
        try:
            complex_input = input(f"Enter complex number #{counter_complex_number} in the form a + bi: ")

            if '+' in complex_input:
                real_part, imaginary_part = complex_input.replace(" ", "").split('+')
                imaginary_part = imaginary_part.rstrip('i')
                imaginary_part = int(imaginary_part)
            if '-' in complex_input:
                real_part, imaginary_part = complex_input.replace(" ", "").split('-')
                imaginary_part = imaginary_part.rstrip('i')
                imaginary_part = int(imaginary_part)
                imaginary_part = -imaginary_part

            real_part = int(real_part)
            list_of_complex_numbers.append(create_complex_number(real_part, imaginary_part))
            counter_complex_number += 1
        except ValueError:
            print("Invalid input, please enter a complex number in the form a + bi.")

    print(f"\nThe list of {number_of_complex_numbers} complex numbers has been created successfully!")
    return list_of_complex_numbers


def print_lists_of_complex_numbers(list_of_complex_numbers: list, list_of_input_complex_numbers: list):
    list_of_complex_numbers.extend(list_of_input_complex_numbers)
    print("Below is displayed the list of " + str(len(list_of_complex_numbers)) + " complex numbers:")
    for i in range(len(list_of_complex_numbers)):
        print(f"z{i + 1} = " + to_str(list_of_complex_numbers[i]))

def print_subarray_of_complex_numbers(starting_index: int, subarray_length: int, list_of_complex_numbers: list):
    print("Display the length and elements of a longest subarray of numbers that contain at most 3 distinct values.\n")
    print("Length: " + str(subarray_length) + "\n")
    for i in range(starting_index, starting_index + subarray_length):
        print(f"z{i + 1 - starting_index} = " + to_str(list_of_complex_numbers[i]))

def print_maximum_subarray_sum_real_parts(maximum_sum: int, starting_index: int, ending_index: int, list_of_complex_numbers: list):
    print("\nDisplay the length and elements of a maximum subarray sum, when considering each number's real part.\n")
    print("Length: " + str(ending_index - starting_index + 1))
    print("The maximum sum is: " + str(maximum_sum) + "\n")
    for i in range(starting_index, ending_index + 1):
        print(f"z{i + 1 - starting_index} = " + to_str(list_of_complex_numbers[i]))

def print_menu():
    menu_options = {
        1: 'Read a list of complex numbers from the console',
        2: 'Display the entire list of numbers to the console',
        3: 'Display the length and elements of a longest subarray of numbers that contain at most 3 distinct values and'
           ' print the length and elements \n    of a maximum subarray sum, when considering each number\'s real part',
        4: 'Exit the program',
    }
    for key in menu_options.keys():
        print(key, '~', menu_options[key])


if __name__ == "__main__":
    print_menu()
    read_numbers = 1
    print_numbers = 2
    solve_subarray_problems = 3
    exit_the_program = 4
    list_of_complex_numbers = generate_random_list_of_complex_numbers()
    while True:
        option = int(input('\nEnter an option from the menu: '))
        if option == read_numbers:
            list_of_input_complex_numbers = read_complex_numbers()
        elif option == print_numbers:
            try:
                print_lists_of_complex_numbers(list_of_complex_numbers, list_of_input_complex_numbers)
            except ValueError:
                print("Please create a list first.")
        elif option == solve_subarray_problems:
            try:
                # naive problem
                longest_subarray_starting_index, maximum_subarray_length = \
                    (longest_subarray_3_distinct_values(list_of_complex_numbers))
                print_subarray_of_complex_numbers(longest_subarray_starting_index, maximum_subarray_length,
                                                  list_of_complex_numbers)
                # dynamic programming problem
                maximum_sum, maximum_sum_starting_index, maximum_sum_ending_index = \
                    (maximum_subarray_sum_real_parts(list_of_complex_numbers))
                print_maximum_subarray_sum_real_parts(maximum_sum, maximum_sum_starting_index, maximum_sum_ending_index,
                                                      list_of_complex_numbers)
            except ValueError:
                print("Please create a list first.")
        elif option == exit_the_program:
            print('You exited the program, thank you!')
            exit()
        else:
            print('Invalid option, please enter a number between 1 and 4.')
