# Solve the problem from the third set here
# 13. Determine the n-th element of the sequence 1,2,3,2,5,2,3,7,2,3,2,5,... obtained from the sequence of
# natural numbers by replacing composed numbers with their prime divisors, without memorizing the elements
# of the sequence.

def is_prime(nr) -> int:
    if nr == 0 or nr == 1:
        return 0
    for d in range(2, int(nr ** 0.5) + 1):
        if nr % d == 0:
            return 0
    return 1


n = input("Enter a number: ")
n = int(n)

c = 2
nr = 2
ok = 0

while c <= n:
    if n == 1:
        print (n)
        break
    if is_prime(nr) == 1:
        if n == c and ok == 0:
            print (nr)
            break
        c += 1
        nr += 1
    elif is_prime(nr) == 0:
        d = 2
        cnr = nr
        for d in range(2,nr//2+1):
            if cnr % d == 0:
                if c == n and ok == 0:
                    print(d)
                    ok = 1
                    break
                while cnr % d == 0:
                    cnr = cnr // d
                c += 1
        nr += 1

