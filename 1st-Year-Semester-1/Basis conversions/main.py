def print_menu():
    """
    Prints the menu options for the application
    """
    menu_options = {
        1: "Add two numbers in a given base",
        2: "Subtract two numbers in a given base",
        3: "Multiply a number by a digit in a given base",
        4: "Divide a number by a digit in a given base",
        5: "Convert a number from a base to another using successive divisions",
        6: "Convert a number from a base to another using substitution method",
        7: "Convert a number from a base to another using 10 as an intermediate base",
        8: "Convert a number using rapid conversions between two bases {2, 4, 8, 16}",
        9: "Exit the program"
    }
    print("")
    for key in menu_options.keys():
        print(key, "~", menu_options[key])

def test_input_base(base: int) -> bool:
    """
    Tests a base to be part of the set {2, 3, ..., 10, 16}
    """
    if base == 16:
        return True
    elif 10 >= base >= 2:
        return True
    return False

def test_input_bases_rapid(base: int, BASE: int) -> bool:
    """
    Tests the two bases for rapid conversion to be in the set {2, 4, 8, 16}
    """
    if (base == 2 or base == 4 or base == 8 or base == 16) and (BASE == 2 or BASE == 4 or BASE == 8 or BASE == 16):
        return True
    return False

def get_first_character(n: str) -> int:
    """
    Returns the first character of a string as an integer, treating it as a hexadecimal digit
    :param n: the input string
    :return: the integer representation of the first character
    """

    return int(n[0], 16)

def get_first_two_characters(n: str) -> int:
    """
    Returns the first two characters of a string as an integer, treating them as hexadecimal digits
    :param n: the input string
    :return: the integer representation of the first two characters
    """

    two_char_string = ""
    two_char_string += n[0]
    two_char_string += n[1]
    return int(two_char_string, 16)

def get_last_character(n: str) -> int:
    """
    Returns the last character of the string as an integer, treating the character as a hexadecimal digit
    :param n: the input string
    :return: the integer representation of the last character
    """

    return int(n[-1], 16)

def get_last_nr_characters(n: str, nr_of_char: int) -> str:
    """
    Returns the last nr_of_char characters from the string n
    """
    last_nr_char = ""
    counter = 1
    while nr_of_char > 0:
        last_nr_char = n[len(n) - counter] + last_nr_char
        counter += 1
        nr_of_char -= 1
    return last_nr_char
    # return n[-nr_of_char:]

def to_hexadecimal(number: int) -> str:
    """
    Converts a number to its hexadecimal representation
    :param number: the number to be converted
    :return: the representation of the number in base 16
    """

    # if the number is lower than 10 than we return it as it is, if not we convert it to base 16
    if number < 10:
        return str(number)
    elif number == 10:
        return "A"
    elif number == 11:
        return "B"
    elif number == 12:
        return "C"
    elif number == 13:
        return "D"
    elif number == 14:
        return "E"
    elif number == 15:
        return "F"

def to_decimal(number: int, base: int) -> int:
    """
    Converts a number from a given base to decimal
    :param number: the number to be converted
    :param base: the base of the number
    :return: the representation of the number in base 10
    """

    number_in_decimal, power = 0, 1
    while number > 0:
        last_digit = number % 10  # get the last digit of the number
        number_in_decimal += last_digit * power  # we add the last digit to the number in decimal
        power *= base  # increase the power with the number's base
        number //= 10  # remove the last digit of the number
    return number_in_decimal

def to_base_2(number: str, base: int) -> str:
    """
        Converts a number from a given base to decimal
        :param number: the number to be converted
        :param base: the base of the number
        :return: the representation of the number in base 2
    """
    return successive_div_conversion(number, base, 2)


def to_base(number: int, base: int) -> int:
    """
    Converts a number from decimal to a given base.
    :param number: the number to be converted
    :param base: the base in which the number will be converted
    :return: the number in the given base
    """

    number_in_base, power = 0, 1
    while number > 0:
        remainder = number % base  # get the remainder of the number
        number_in_base += remainder * power  # we add the last digit to the number in base
        power *= 10  # increase the power with 10
        number //= base  # reduce the number to its quotient
    return number_in_base

def addition(a: str, b: str, base: int) -> str:
    """
    Addition of two numbers (a, b) in a given base (base)
    :param a: the first number
    :param b: the second number
    :param base: the base of the two numbers
    :return: the sum of the two numbers in a given base
    """

    summ = 0
    # addition for numbers in base {2,3,...,10}
    if base <= 10:
        a = int(a)
        b = int(b)
        summ = 0
        carry = 0
        power = 1
        maxx = max(len(str(a)), len(str(b)))  # to find out which number has more characters

        for i in range(maxx):
            digits_sum = a % 10 + b % 10 + carry  # calculate the sum of the 2 last digits of a and b with carry
            summ += (digits_sum % base) * power  # add to the sum the modulo between the digits sum and the base
            carry = digits_sum // base  # set the carry to 1 if the digits sum >= base or else to 0
            # remove the last digit of numbers a, b and increase the power with 10
            a //= 10
            b //= 10
            power *= 10

        if carry > 0:
            summ += carry * power  # check for the last carry

        summ = str(summ)

    # addition for numbers in base 16
    elif base == 16:
        summ = ""
        carry = 0
        maxx = max(len(a), len(b))  # to find out which number has more characters

        # add insignificant zeros in front of the number with fewer characters to make them equal in length
        while len(a) != len(b):
            if len(a) < len(b):
                a = "0" + a
            else:
                b = "0" + b

        for i in range(maxx):
            # calculate the sum of the 2 last digits (characters) of a and b with carry
            digits_sum = get_last_character(a) + get_last_character(b) + carry
            # we convert the digits sum to base 16 and set the carry to 1 if the digits sum >= 16
            if digits_sum >= 16:
                summ = to_hexadecimal(digits_sum - 16) + summ
                carry = 1
            else:
                summ = to_hexadecimal(digits_sum) + summ
                carry = 0
            # remove the last character of numbers a, b
            a = a[:-1]
            b = b[:-1]

        if carry > 0:
            summ = to_hexadecimal(carry) + summ  # check for the last carry

    return summ

def subtraction(a: str, b: str, base: int) -> str:
    """
    Subtraction of two numbers (a, b) in a given base (base) , where a > b
    :param a: the first number
    :param b: the second number
    :param base: the base of the two numbers
    :return: the difference of the two numbers in a given base
    """

    diff = 0
    # subtraction for numbers in base {2,3,...,10}
    if base <= 10:
        a = int(a)
        b = int(b)
        diff = 0
        borrow = 0
        power = 1

        while a > 0:
            # get the last digits of a and b and then eliminate them
            last_digit_a = a % 10
            last_digit_b = b % 10
            a = a // 10
            b = b // 10
            digits_sub = last_digit_a - last_digit_b + borrow  # subtract the last digits of a and b with borrow
            # if the subtraction of the last digits is negative we set the borrow to -1 and add the base to the
            # subtraction so the resulted digit becomes positive, if not the borrow is set to 0
            if digits_sub < 0:
                borrow = -1
                digits_sub += base
            else:
                borrow = 0
            diff += digits_sub * power  # add to diff the final result of digits sub
            power = power * 10  # increase the power with 10

        diff = str(diff)

    # subtraction for numbers in base 16
    elif base == 16:
        diff = ""
        borrow = 0

        while len(a) != len(b):
            b = "0" + b  # add insignificant zeros to b to make it the same length as a

        for i in range(len(a)):
            # calculate the differentiation of the 2 last digits (characters) of a and b with borrow
            digit_sub = get_last_character(a) - get_last_character(b) + borrow
            # we convert the digits sub to base 16 and set the borrow to -1 if the digits sub < 0
            if digit_sub < 0:
                diff = to_hexadecimal(digit_sub + 16) + diff
                borrow = -1
            else:
                diff = to_hexadecimal(digit_sub) + diff
                borrow = 0
            # remove the last character of numbers a, b
            a = a[:-1]
            b = b[:-1]

    return diff

def multiplication(a: str, b: str, base: int) -> str:
    """
    Multiplication of two numbers (a, b) in a given base (base), where b has only one digit
    :param a: the number to be multiplied
    :param b: the digit to multiply by
    :param base: the base of the two numbers
    :return: the product of the number and the digit in the given base
    """

    product = 0
    # multiplication for numbers in base {2,3,...,10}
    if base <= 10:
        a = int(a)
        b = int(b)
        product = 0
        carry = 0
        power = 1

        while a > 0:
            last_digit = a % 10  # get the last digit of number a
            # multiply the last digit with the given number b and add the carry
            digits_product = (last_digit * b) + carry
            # add to the product the modulo between the digits product and the base
            product += (digits_product % base) * power
            carry = digits_product // base  # set the carry with the quotient between the digits product and the base
            # remove the last digit of a and increase the power with 10
            a = a // 10
            power *= 10

        if carry > 0:
            product += carry * power  # check for the last carry

        product = str(product)

    # multiplication for numbers in base 16
    elif base == 16:
        product = ""
        carry = 0

        for i in range(len(a)):
            # calculate the product between the last digits (characters) of a and b with carry
            digits_product = get_last_character(a) * get_last_character(b) + carry
            product = to_hexadecimal(digits_product % 16) + product  # add to the product the digits product in base 16
            carry = digits_product // 16  # set the carry with the quotient between the digits product and base 16
            a = a[:-1]  # remove the last digit (character) of the number

        if carry > 0:
            product = to_hexadecimal(carry) + product  # check for the last carry

    return product

def division(a: str, b: str, base: int) -> tuple:
    """
    Division of two numbers (a, b) in a given base (base), where b has only one digit
    :param a: the number to be divided
    :param b: the digit to divide by
    :param base: the base of the two numbers
    :return: the quotient and the remainder of the division
    """

    quotient = 0
    # division for numbers in base {2,3,...,10}
    if base <= 10:
        a = int(a)
        b = int(b)
        quotient = 0
        borrow = 0

        while a >= b:
            power = 1
            # power has the same number of digits as a
            while power * 10 < a:
                power *= 10
            first_digits = a // power  # take the first digit
            # if the first digit is less than b that means we can't divide it, so we take the first two digits
            if first_digits < b and borrow != 0:
                power //= 10
                first_digits = a // power
            first_digits = to_decimal(first_digits, base)  # transform the first digits to base 10
            borrow = first_digits % b  # set the borrow to the modulo between the first digit/digits and b
            # we add to the quotient the division result between first digit/digits and b
            quotient = quotient * 10 + first_digits // b
            length1 = len(str(a)) - 1
            a = borrow * power + a % power  # prepare the number for the next division
            length2 = len(str(a))
            while length1 > length2:  # check for 0's
                quotient = quotient * 10
                length1 -= 1

    # division for numbers in base 16
    elif base == 16:
        quotient = ""

        while int(a, 16) >= int(b, 16):
            # check if the first digit is less than b
            if int(a[0], 16) < int(b, 16):
                # if it is, it means we can't divide it, so we take the first two digits and divide them with b
                digit_div = get_first_two_characters(a) // get_last_character(b)
                quotient = quotient + to_hexadecimal(digit_div)  # add to the quotient the result of the division
                # set the borrow to the modulo between the first two digits (characters) and b
                borrow = get_first_two_characters(a) % get_last_character(b)
                a = to_hexadecimal(borrow) + a[2:]  # prepare the number for the next division
            else:
                # if not we divide only the first digit
                digit_div = get_first_character(a) // get_last_character(b)
                quotient = quotient + to_hexadecimal(digit_div)  # add to the quotient the result of the division
                # set the borrow to the modulo between the first two digits (characters) and b
                borrow = get_first_character(a) % get_last_character(b)  # FIXME am schimbat cu get first chr
                a = to_hexadecimal(borrow) + a[1:]  # prepare the number for the next division

    remainder = a
    return quotient, remainder

def successive_div_conversion(n: str, BASE_n: int, base: int) -> str:
    """
    Converts a number from one base to another using the method of successive divisions (BASE_n > base)
    :param n: the number to be converted
    :param BASE_n: the base of the input number
    :param base: the base to convert to
    :return: the converted number in the new base (base)
    """

    converted_number = 0
    # conversion for numbers in base {2,3,...,10}
    if BASE_n <= 10:
        n = int(n)
        list_of_remainders = []  # list to hold all the remainders

        while n > 0:
            # we use the division by one digit algorithm to get the quotient and the remainder between the given number
            # and the base we want to convert it to
            quotient, remainder = division(n, str(base), BASE_n)
            list_of_remainders.append(remainder)  # add the remainder to the list
            n = quotient  # assign the value of the quotient to be the next number to be divided

        # inverse the list of remainders and then join them together to form the converted number
        list_of_remainders.reverse()
        converted_number = ""
        for i in range(len(list_of_remainders)):
            converted_number += str(list_of_remainders[i])

    # conversion for numbers in base 16
    elif BASE_n == 16:
        list_of_remainders = []

        while len(n) > 0:
            # we use the division by one digit algorithm to get the quotient and the remainder between the given number
            # and 16 (the base we want to convert it to)
            quotient, remainder = division(n, str(base), 16)
            list_of_remainders.append(remainder)  # add the remainder to the list
            n = quotient  # assign the value of the quotient to be the next number to be divided

        # inverse the list of remainders and then join them together to form the converted number
        list_of_remainders.reverse()
        converted_number = ""
        for i in range(len(list_of_remainders)):
            converted_number += str(list_of_remainders[i])

    return converted_number

def substitution_conversion(n: str, base_n: int, BASE: int) -> str:
    """
    Converts a number from one base to another using the substitution method (base_n < BASE)
    :param n: the number to be converted
    :param base_n: the base of the input number
    :param BASE: the base to convert to
    :return: the converted number in the new base (BASE)
    """

    converted_number = 0
    # conversion for numbers to base {2,3,...,10}
    if BASE <= 10:
        converted_number = 0

        for i in range(len(n)):
            last_digit = int(n[-1])  # get the last digit of the number
            for _ in range(i):
                # multiply the last digit of the number with the base of the number as many times as the position of
                # the last digit requires (i) and then the result of the multiplication is converted in the wanted BASE
                last_digit = int(multiplication(str(last_digit), str(base_n), BASE))

            # the result of the multiplications is added to the converted number
            converted_number = addition(converted_number, str(last_digit), BASE)
            n = n[:-1]  # remove the last digit (character) of the number

    # conversion for numbers to base 16
    elif BASE == 16:
        converted_number = ""

        for i in range(0, len(str(n))):
            last_digit = n[-1]  # get the last digit (character) of the number
            for _ in range(i):
                # multiply the last digit of the number with the base of the number as many times as the position of
                # the last digit requires (i) and then the result of the multiplication is converted in the wanted BASE
                last_digit = multiplication(last_digit, str(base_n), BASE)

            # the result of the multiplications is added to the converted number
            converted_number = addition(converted_number, last_digit, BASE)
            n = n[:-1]  # remove the last digit (character) of the number

    return converted_number

def simple_conversion(n: str, BASE_n: int, base: int) -> str:
    """
    Converts a number from one base to another using 10 as an intermediate base
    :param n: the number to be converted
    :param BASE_n: the base of the input number
    :param base: the base to convert to
    :return: the converted number
    """

    converted_number, power = 0, 1
    # conversion for numbers in base {2,3,...,10}
    if BASE_n <= 10:
        n = int(n)
        n = to_decimal(n, BASE_n)  # convert the number to its decimal form
        converted_number = to_base(n, base)  # convert the decimal form of the number to the given base
        converted_number = str(converted_number)

    # conversion for numbers in base 16
    elif BASE_n == 16:
        converted_number, power = 0, 1

        # convert the number from base 16 to base 10
        while len(n) > 0:
            last_digit = get_last_character(n)  # get the last digit (character) of the number
            converted_number += last_digit * power  # we add the last digit to the converted number
            power *= 16  # increase the power with 16
            n = n[:-1]  # remove the last digit (character) of the number

        n = converted_number
        converted_number, power = "", 1

        # convert the number from base 10 to the given base
        while n > 0:
            last_digit = n % base  # get the last digit (character) of the number
            converted_number = str(last_digit) + converted_number  # we add the last digit to the converted number
            power *= 10  # increase the power with 10
            n //= base  # reduce the number to its quotient in the given base

    return converted_number

def rapid_conversions(n: str, BASE_n: int, base: int) -> str:
    """
    Converts a number from one base to another using rapid conversion (for bases 2, 4, 8, 16)
    :param n: the number to be converted
    :param BASE_n: the base of the input number
    :param base: the base to convert to
    :return: the converted number
    """

    converted_number = ""
    # dictionary that holds the number of binary digits that need to be grouped for each base
    groupings = {
        4: 2,
        8: 3,
        16: 4
    }

    if BASE_n != 2:
        n = to_base_2(n, BASE_n)  # convert the number to base 2

    if base != 2:
        while n:
            digits = get_last_nr_characters(n, int(groupings[base]))  # returns the last 2/3/4 digits of n
            digits = substitution_conversion(digits, 2, base)  # converts the digits from base 2 to the desired base
            converted_number = converted_number + str(digits)  # add the digits to the converted number
            n = n[:-groupings[base]]  # removes last 2/3/4 digits from n

        converted_number = converted_number[::-1]  # reverse the string with the result
    else:
        converted_number = n

    return converted_number


if __name__ == "__main__":
    print("Implementation operations and conversions ~ Beudean Carmen")
    while True:
        print_menu()
        option = int(input("\nEnter an option from the menu: "))
        print("")
        if option == 1:
            print("Add two numbers in a given base")
            base = int(input("Enter the base you want to work with: base = "))
            if test_input_base(base):
                a = input(f"Enter the first number in base {base}: ")
                b = input(f"Enter the second number in base {base}: ")
                print(f"The sum of the numbers {a} and {b} is " + addition(a, b, base))
            else:
                print("\nInvalid base. Please enter a base from the set {2, 3, ... ,10, 16}.")
            print("")
            input("Press enter to continue...")

        elif option == 2:
            print("Subtract two numbers in a given base")
            base = int(input("Enter the base you want to work with: base = "))
            if test_input_base(base):
                a = input(f"Enter the first number in base {base}: ")
                b = input(f"Enter the second number in base {base}: ")
                print(f"The difference of the numbers {a} and {b} is " + subtraction(a, b, base))
            else:
                print("\nInvalid base. Please enter a base from the set {2, 3, ... ,10, 16}.")
            print("")
            input("Press enter to continue...")

        elif option == 3:
            print("Multiply a number by one digit in a given base")
            base = int(input("Enter the base you want to work with: base = "))
            if test_input_base(base):
                a = input(f"Enter a number in base {base}: ")
                b = input(f"Enter a digit in base {base}: ")
                print(f"The product of the numbers {a} and {b} is " + multiplication(a, b, base))
            else:
                print("\nInvalid base. Please enter a base from the set {2, 3, ... ,10, 16}.")
            print("")
            input("Press enter to continue...")

        elif option == 4:
            print("Divide a number by one digit in a given base")
            base = int(input("Enter the base you want to work with: base = "))
            if test_input_base(base):
                a = input(f"Enter a number in base {base}: ")
                b = input(f"Enter a digit in base {base}: ")
                quotient, remainder = division(a, b, base)
                print(f"From the division of the numbers {a} and {b} results the quotient {quotient} "
                      f"and the remainder {remainder}")
            else:
                print("\nInvalid base. Please enter a base from the set {2, 3, ... ,10, 16}.")
            print("")
            input("Press enter to continue...")

        elif option == 5:
            print("Convert a number to another base using the successive divisions method")
            BASE = int(input("Enter a base you want to convert from: "))
            base = int(input("Enter a base you want to convert to: "))
            if test_input_base(base) and test_input_base(BASE) and BASE != base:
                n = input(f"Enter number in base {BASE}: ")
                print(f"The converted number in base {base} is " + successive_div_conversion(n, BASE, base))
            else:
                print("\nInvalid bases. Please enter two distinct bases from the set {2, 3, ... ,10, 16}.")
            print("")
            input("Press enter to continue...")

        elif option == 6:
            print("Convert a number to another base using the substitution method")
            base = int(input("Enter a base you want to convert from: "))
            BASE = int(input("Enter a base you want to convert to: "))
            if test_input_base(base) and test_input_base(BASE) and BASE != base:
                n = input(f"Enter a number in base {base}: ")
                print(f"The converted number in base {BASE} is " + substitution_conversion(n, base, BASE))
            else:
                print("\nInvalid bases. Please enter two distinct bases from the set {2, 3, ... ,10, 16}.")
            print("")
            input("Press enter to continue...")

        elif option == 7:
            print("Convert a number to another base using 10 as an intermediate base")
            BASE = int(input("Enter a base you want to convert from: "))
            base = int(input("Enter a base you want to convert to: "))
            if test_input_base(base) and test_input_base(BASE) and BASE != base:
                n = input(f"Enter number in base {BASE}: ")
                print(f"The converted number in base {base} is " + simple_conversion(n, BASE, base))
            else:
                print("\nInvalid bases. Please enter two distinct bases from the set {2, 3, ... ,10, 16}.")
            print("")
            input("Press enter to continue...")

        elif option == 8:
            print("Convert a number to another base using rapid conversions where both bases are from the "
                  "set {2, 4, 8, 16}")
            BASE = int(input("Enter a base you want to convert from: "))
            base = int(input("Enter a base you want to convert to: "))
            if test_input_bases_rapid(base, BASE) and BASE != base:
                n = input(f"Enter number in base {BASE}: ")
                print(f"The number converted in base {base} is " + rapid_conversions(n, BASE, base))
            else:
                print("\nInvalid bases. Please enter two distinct bases from the set {2, 4, 8, 16}.")
            print("")
            input("Press enter to continue...")

        elif option == 9:
            print("You exited the program, thank you!")
            exit()

        else:
            print("Invalid option, please enter a number between 1 and 9.")
