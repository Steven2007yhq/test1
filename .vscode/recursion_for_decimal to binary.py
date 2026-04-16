import random

b=[]
def convert(n):
    
    if(n<=1):
        b.append(n)
    else:
        b.append(n&1)
        convert(n//2)

for i in range(1,101):
  n=random.randint(1,1000)
  convert(n)
  b.reverse()
  print(f"n的值为{n}，其二进制为：")
  for j in b:
    print(j,end="")
  b.clear()
  print("\n")