#include <stdio.h>
#include <stdlib.h>

void print_menu() {
    /*
     * Prints the console menu
     */

    printf("1. Read a vector of numbers\n");
    printf("2. The number of 0 digits of the product of the read numbers\n");
    printf("3. The longest contiguous subsequence where the sum of any two consecutive elements is a prime number\n");
    printf("4. Exit the program\n");
}

void read_vector(int vector[], int* size) {
    /*
     * Reads the vector and its size from the keyboard
     vector - the vector of elements
     *size - the pointer that holds the address to the size of the vector
     */

    printf("Enter the number of elements of the vector:");
    scanf("%d", size);

    printf("Enter %d elements:", *size);

    for (int i = 1; i <= *size; i++) {
        scanf("%d", &vector[i]);
    }

    printf("The following vector was read successfully: \n");
    for (int i = 1; i <= *size; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n\n");
}

/// problem 6

/// a. Read a sequence of natural numbers and determine the number of 0 digits of the product
/// of the read numbers.

void prime_decomposition(int element, int* counter_2, int* counter_5) {
    /*
     * Updates the counters of 2's and 5's in the decomposition of each element from the vector
     element - the element to decompose
     counter_2 - the number of 2's in the decomposition of element
     counter_5 - the number of 5's in the decomposition of element
     */

    if (element % 2 == 0) {
        while (element % 2 == 0 && element != 0) {
            element = element / 2;
            *counter_2 = *counter_2 + 1;
        }
    }
    if (element % 5 == 0) {
        while (element % 5 == 0 && element != 0) {
            element = element / 5;
            *counter_5 = *counter_5 + 1;
        }
    }
}

int zero_digits_product(int vector[], int size) {
    /*
     * Returns the number of 0 digits of the product of the vector's elements
     vector - the vector of elements
     size - the number of elements of the vector
     */

    int counter_2 = 0, counter_5 = 0;
    for (int i = 1; i <= size; i++) {
        prime_decomposition(vector[i], &counter_2, &counter_5);
    }
    if (counter_2 < counter_5)
        return counter_2;
    else
        return counter_5;
}

/// b. Given a vector of numbers, find the longest contiguous subsequence such that the sum of any two consecutive
/// elements is a prime number.

int is_prime(int element) {
    /*
     * Checks if the given element is prime
     */

    if (element == 0 || element == 1)
        return 0;
    for (int d = 2; d * d <= element; d++) {
        if (element % d == 0) {
            return 0;
        }
    }
    return 1;
}

void longest_contiguous_subsequence(int vector[], int size) {
    /*
     * Prints the longest contiguous subsequence of numbers from the vector where the sum of any 2 consecutive
     elements is a prime number.
     vector - the vector of elements
     size - the number of elements of the vector
     */

    int start = 0, end = 0, len = 1, max_len = 1, start_ok = 0, max_start;
    for (int i = 1; i < size; i++) {
        int sum = vector[i] + vector[i + 1];
        if (is_prime(sum) == 1) {
            if (start_ok == 0) {
                start_ok = 1;
                start = i;
            }
            len = len + 1;
        }
        else {
            len = 1;
            start_ok = 0;
        }
        if (len > max_len)
        {
            max_start = start;
            max_len = len;
            end = start + len - 1;
        }
    }
    if (start == 0 && end == 0) {
        printf("There is no such subsequence.\n");
    }
    else {
        printf("The longest contiguous subsequence where the sum of any two consecutive elements is a prime number is: \n");
        for (int i = max_start; i <= end; i++) {
            printf("%d ", vector[i]);
        }
        printf("\n\n");
    }
}

int main() {
    int option, vector[101], size = 0;
    while (1) {
        print_menu();
        printf("Enter an option from the menu:");
        scanf("%d", &option);
        printf("\n");
        switch (option) {
        case 1:
        {
            read_vector(vector, &size);
            break;
        }
        case 2:
        {
            if (size == 0) {
                printf("The vector is empty.\n\n");
                break;
            }
            int zero_digits = zero_digits_product(vector, size);
            printf("The number of 0 digits of the product of the read numbers is: %d\n\n", zero_digits);
            break;
        }
        case 3:
        {
            if (size == 0) {
                printf("The vector is empty.\n\n");
                break;
            }
            longest_contiguous_subsequence(vector, size);
            break;
        }
        case 4:
        {
            printf("You exited the program");
            exit(0);
            break;
        }
        default:
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }
    return 0;
}
