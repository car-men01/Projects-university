# Solve the problem from the first set here
# 5. Generate the largest prime number smaller than a given natural number n.
# If such a number does not exist, a message should be displayed.

def is_prime (m: int) -> int:
    if m==0 or m==1:
        return 0
    for d in range(2, int(m**0.5)+1):
        if m%d==0:
            return 0
    return 1

n = input ("Enter a number: ")
m = int(n)-1

while m>0:
    if is_prime(m)==1:
        print(m)
        break
    if m==1:
        print("There exist no such number.")
    m=m-1
