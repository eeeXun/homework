def prime():
    import math
    listPrime=[2]
    a=2
    while True:
        isprime=True
        for i in listPrime:
            if a%i == 0 and a!=2:
                isprime=False
                break
            if i>math.sqrt(a):
                break
        if isprime:
            yield a
            listPrime.append(a)
        a+=1
            

n = eval(input("How many prime numbers do you want to get? "))
p = prime()
for i in range(n):
    print(next(p))