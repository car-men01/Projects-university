# Solve the problem from the second set here
# 7. Determine the twin prime numbers p1 and p2 immediately larger than the given non-null natural number n.
# Two prime numbers p and q are called twin if q - p = 2.

def is_prime (m: int) -> int:
    if m==0 or m==1:
        return 0
    for d in range(2, int(m**0.5)+1):
        if m%d==0:
            return 0
    return 1

n = input ("Enter a number: ")
p1 = int(n)+1
p2 = int(n)+3

while True:
    if is_prime(p1)==1 and is_prime(p2)==1:
        print(p1, p2)
        break
    p1+=1
    p2+=1