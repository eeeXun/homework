import random
print("You have $5.")
print("Big or Small?")
money=5

while money>0 and money<10:
    m=random.randint(1,6)
    n=random.randint(1,6)
    s=random.randint(1,6)
    p=input()
    if(p=='b'):
        if(m+n+s>=11):
            money=money+1
            print("The numbers are (",m,",",n,",",s,"). You win.")
            print("You have $",money,".")
        else:
            money=money-1
            print("The numbers are (",m,",",n,",",s,"). You lose.")
            if(money==0):
                print("You have $0.")
                print("Sorry.  You lost all your money!")
            else:
                print("You have $",money,".")
    else:
        if(m+n+s<=10):
            money=money+1
            print("The numbers are (",m,",",n,",",s,"). You win.")
            print("You have $",money,".")
        else:
            money=money-1
            print("The numbers are (",m,",",n,",",s,"). You lose.")
            if(money==0):
                print("You have $0.")
                print("Sorry.  You lost all your money!")
            else:
                print("You have $",money,".")
