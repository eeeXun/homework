import random
print("Hello! What is your name?")
name=input()
print("Well, "+name+", I am thinking of a number between 1 and 20.")
number=random.randint(1,20)

while(1>0):
    print("Take a guess.")
    g=int(input())
    if(g>number):
        print("Your guess is too high.")
    if(g<number):
        print("Your guess is too low.")
    if(g==number):
        print("Good job, "+name+"! You guessed my number in 20 guesses!")
        break
