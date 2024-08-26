# problem 2
# Consider a positive number n. Determine all its decompositions as sums of prime numbers.
# iterative and recursive algorithm


def is_prime(number):
    if number == 0 or number == 1:
        return False
    for divisor in range(2, int(number ** 0.5) + 1):
        if number % divisor == 0:
            return False
    return True


def recursive_backtracking_decompose_sum_of_primes(input_number, prime_numbers_sum=None):
    if prime_numbers_sum is None:
        prime_numbers_sum = []
    if input_number == 0:
        print(prime_numbers_sum)
    for i in range(2, input_number + 1):
        if is_prime(i) and (not prime_numbers_sum or i >= prime_numbers_sum[-1]):
            recursive_backtracking_decompose_sum_of_primes(input_number - i, prime_numbers_sum + [i])


def iterative_backtracking_decompose_sum_of_primes(input_number):
    number_to_decompose_list = [input_number]
    prime_numbers_sum_list = [[]]
    while number_to_decompose_list:
        number_left_to_decompose = number_to_decompose_list.pop()
        prime_numbers_sum = prime_numbers_sum_list.pop()
        if number_left_to_decompose == 0:
            print(prime_numbers_sum)
        elif number_left_to_decompose > 0:
            for i in range(number_left_to_decompose, 1, -1):
                if is_prime(i) and (not prime_numbers_sum or i >= prime_numbers_sum[-1]):
                    number_to_decompose_list.append(number_left_to_decompose - i)
                    prime_numbers_sum_list.append(prime_numbers_sum + [i])


while True:
    input_number = int(input('Enter a positive number: '))
    print(('All the decompositions below as sums of prime numbers of the positive number ' + str(input_number) +
           ' were determined using an iterative backtracking algorithm:\n'))
    iterative_backtracking_decompose_sum_of_primes(input_number)
    print('')
    input_number = int(input('Enter a positive number: '))
    print(('All the decompositions below as sums of prime numbers of the positive number ' + str(input_number) +
           ' were determined using a recursive backtracking algorithm:\n'))
    recursive_backtracking_decompose_sum_of_primes(input_number)
    break
