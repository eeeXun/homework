import random

def Number():
    a=list(range(10))
    number=''
    random.shuffle(a)
    for i in range(4):
        number+=str(a[i])
    return number

def getGuess():
    while True:
        guess=input()
        
        repeatDigit=False
        for i in range(3):
            for j in range(i+1,4):
                if guess[i]==guess[j]:
                   repeatDigit=True
        notDigit=False
        for i in range(4):
            if ord(guess[i])>57 or ord(guess[i])<48:
                notDigit=True
        if len(guess)!=4:
            print('Please input 4 digits.')
        elif notDigit:
            print('Please input 4 digits.')
        elif repeatDigit:
            print('There are repeated digits in your guess,please input it again.')
        else:
            return guess

def Judge(number,guess):
    A=0
    B=0
    temp=0
    for i in range(4):
        if guess[i]==number[i]:
            A+=1
    for i in range(4):
        if guess[i] in number:
            temp+=1
    B=temp-A
    return A,B

def Playagain():
    print('Do you want to play again?Please input (yes,y),or (no,n)')
    again=input()
    again=again.lower()
    while(again!='yes'and again!='y'and again!='no' and again!='n'):
        print('Please input (yes,y),or (no,n)')
        again=input()
        again=again.lower()
    if(again=='yes'or again=='y'):
        return True
    else:
        return False

while True:
    print('''I am thinking of a 4-digit number. Try to guess what it is.
The clues I give are...
When I say: That means:
  A         One digit is correct and in the right position.
  B         One digit is correct but in the wrong position.''')
    time=1
    number=Number()
    print(number)
    while True:
        print('Guess #%s: '%(time),end='')
        guess=getGuess()
        A,B=Judge(number,guess)
        if A==0 and B==0:
            print('Sorry,you don\'t hit any digit,guess it again.')
        else:
            if A>0:
                print('%sA'%(A),end='')
            if B>0:
                print('%sB'%(B),end='')
            print()
            if A==4:
                print('Yes,you win.It takes you %s guesses to find the answer.'%(time))
                break
            time+=1
    if not Playagain():
        break