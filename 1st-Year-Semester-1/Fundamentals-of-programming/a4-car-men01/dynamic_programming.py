# problem 1
# Determine the longest common subsequence of two given sequences. Subsequence elements are not required to occupy
# consecutive positions. For example, if X = "MNPNQMN" and Y = "NQPMNM", the longest common subsequence has length 4,
# and can be one of "NQMN", "NPMN" or "NPNM". Determine and display both the length of the longest common subsequence
# as well as at least one such subsequence.
# naive, non-optimized version (recursive) and dynamic programming version


def longest_common_subsequence_length(sequence_1, sequence_2, length_sequence_1, length_sequence_2):
    if length_sequence_1 == 0 or length_sequence_2 == 0:
        return 0
    elif sequence_1[length_sequence_1 - 1] == sequence_2[length_sequence_2 - 1]:
        return 1 + longest_common_subsequence_length(sequence_1, sequence_2, length_sequence_1 - 1,
                                                     length_sequence_2 - 1)
    else:
        return max(longest_common_subsequence_length(sequence_1, sequence_2, length_sequence_1, length_sequence_2 - 1),
                   longest_common_subsequence_length(sequence_1, sequence_2, length_sequence_1 - 1, length_sequence_2))


def longest_common_subsequence(sequence_1, sequence_2, length_sequence_1, length_sequence_2):
    if length_sequence_1 == 0 or length_sequence_2 == 0:
        return ""
    elif sequence_1[length_sequence_1 - 1] == sequence_2[length_sequence_2 - 1]:
        return (longest_common_subsequence(sequence_1, sequence_2, length_sequence_1 - 1, length_sequence_2 - 1)
                + sequence_1[length_sequence_1 - 1])
    else:
        if (longest_common_subsequence_length(sequence_1, sequence_2, length_sequence_1, length_sequence_2 - 1)
                > longest_common_subsequence_length(sequence_1, sequence_2, length_sequence_1 - 1, length_sequence_2)):
            return longest_common_subsequence(sequence_1, sequence_2, length_sequence_1, length_sequence_2 - 1)
        else:
            return longest_common_subsequence(sequence_1, sequence_2, length_sequence_1 - 1, length_sequence_2)


def print_matrix_of_lengths(matrix):
    for i in matrix:
        print(" ".join(map(str, i)))
    print("")


def longest_common_subsequence_dynamic_programming(sequence_1, sequence_2, length_sequence_1, length_sequence_2):
    matrix_of_lengths = [[0] * (length_sequence_2 + 1) for i in
                         range(length_sequence_1 + 1)]  # initialize elements of matrix with 0
    for i in range(length_sequence_1):  # we start building up the matrix
        for j in range(length_sequence_2):
            if sequence_1[i] == sequence_2[j]:
                matrix_of_lengths[i + 1][j + 1] = matrix_of_lengths[i][j] + 1
                print_matrix_of_lengths(matrix_of_lengths)
            else:
                matrix_of_lengths[i + 1][j + 1] = max(matrix_of_lengths[i][j + 1], matrix_of_lengths[i + 1][j])
    print_matrix_of_lengths(matrix_of_lengths)
    print("")
    
    # the last element of the matrix is the longest common length
    longest_common_sequence_length = matrix_of_lengths[length_sequence_1][length_sequence_2]
    # we create an empty list with the number of elements of the matrix
    longest_common_sequence = [''] * longest_common_sequence_length  
    i = length_sequence_1
    j = length_sequence_2
    while i > 0 and j > 0:
        # we check starting from the last character if the elements are equal, and then we store them in long. comm seq
        if sequence_1[i - 1] == sequence_2[j - 1]:
            longest_common_sequence[longest_common_sequence_length - 1] = sequence_1[i - 1]
            i -= 1
            j -= 1
            longest_common_sequence_length -= 1
        elif matrix_of_lengths[i - 1][j] > matrix_of_lengths[i][j - 1]:
            i -= 1
        else:
            j -= 1
        print(longest_common_sequence)

    return matrix_of_lengths[length_sequence_1][length_sequence_2], ''.join(longest_common_sequence)


while True:
    input_sequence_1 = input('Enter the first sequence: ')  # MNPNQMN
    input_sequence_2 = input('Enter the second sequence: ')  # NQPMNM
    length_sequence_1 = len(input_sequence_1)
    length_sequence_2 = len(input_sequence_2)

    # naive, recursive
    length_of_longest_common_sequence = (
        longest_common_subsequence_length(input_sequence_1, input_sequence_2, length_sequence_1, length_sequence_2))
    example_of_longest_common_sequence = (
        longest_common_subsequence(input_sequence_1, input_sequence_2, length_sequence_1, length_sequence_2))
    print('The longest common sequence between the sequences ' + str(input_sequence_1) + ' and ' +
          str(input_sequence_2) + ' was determined using a naive, recursive, non-optimized algorithm.\n')
    print('The length of the longest common subsequence is: ' + str(length_of_longest_common_sequence))
    print('An example of such a sequence is: ' + str(example_of_longest_common_sequence))
    print('')

    # dynamic programming
    length_of_longest_common_sequence, example_of_longest_common_sequence = (
        longest_common_subsequence_dynamic_programming(input_sequence_1, input_sequence_2, length_sequence_1,
                                                       length_sequence_2))
    print('The longest common sequence between the sequences ' + str(input_sequence_1) + ' and ' +
          str(input_sequence_2) + ' was determined using an optimized dynamic programming algorithm.\n')
    print('The length of the longest common subsequence is: ' + str(length_of_longest_common_sequence))
    print('An example of such a sequence is: ' + str(example_of_longest_common_sequence))
    break
