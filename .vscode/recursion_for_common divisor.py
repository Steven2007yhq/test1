import random


def gcd(n, m):
    
    if m == 0:
        return n
    
    if n % m == 0:
        return m
    else:
        return gcd(m, n % m)
for i in range(1,101):
    n=random.randint(0,10000)
    m=random.randint(0,10000)
    result=gcd(max(n,m),min(n,m))
    print(f"第{i}组:n={n},m={m},最大公约数:{result}")



