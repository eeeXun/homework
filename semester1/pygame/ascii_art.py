import random
picture=['''  , ,, ,                              
   | || |    ,/  _____  \.''',
'''  , ,, ,                              
   | || |    ,/  _____  \.             
   \_||_/    ||_/     \_||             
     ||       \_| . . |_/''',
'''  , ,, ,                              
   | || |    ,/  _____  \.             
   \_||_/    ||_/     \_||             
     ||       \_| . . |_/              
     ||         |  L  |                
    ,||         |`==='|''',
'''  , ,, ,                              
   | || |    ,/  _____  \.             
   \_||_/    ||_/     \_||             
     ||       \_| . . |_/              
     ||         |  L  |                
    ,||         |`==='|                
    |>|      ___`>  -<'___             
    |>|\    /             \\''',
'''  , ,, ,                              
   | || |    ,/  _____  \.             
   \_||_/    ||_/     \_||             
     ||       \_| . . |_/              
     ||         |  L  |                
    ,||         |`==='|                
    |>|      ___`>  -<'___             
    |>|\    /             \            
    \>| \  /  ,    .    .  |           
     ||  \/  /| .  |  . |  |''',
  '''  , ,, ,                              
   | || |    ,/  _____  \.             
   \_||_/    ||_/     \_||             
     ||       \_| . . |_/              
     ||         |  L  |                
    ,||         |`==='|                
    |>|      ___`>  -<'___             
    |>|\    /             \            
    \>| \  /  ,    .    .  |           
     ||  \/  /| .  |  . |  |           
     ||\  ` / | ___|___ |  |     (     
  (( || `--'  | _______ |  |     ))  (''',
'''  , ,, ,                              
   | || |    ,/  _____  \.             
   \_||_/    ||_/     \_||             
     ||       \_| . . |_/              
     ||         |  L  |                
    ,||         |`==='|                
    |>|      ___`>  -<'___             
    |>|\    /             \            
    \>| \  /  ,    .    .  |           
     ||  \/  /| .  |  . |  |           
     ||\  ` / | ___|___ |  |     (     
  (( || `--'  | _______ |  |     ))  ( 
(  )\|| (  )\ | - --- - | -| (  ( \  ))
(\/  || ))/ ( | -- - -- |  | )) )  \((''',
'''  , ,, ,                              
   | || |    ,/  _____  \.             
   \_||_/    ||_/     \_||             
     ||       \_| . . |_/              
     ||         |  L  |                
    ,||         |`==='|                
    |>|      ___`>  -<'___             
    |>|\    /             \            
    \>| \  /  ,    .    .  |           
     ||  \/  /| .  |  . |  |           
     ||\  ` / | ___|___ |  |     (     
  (( || `--'  | _______ |  |     ))  ( 
(  )\|| (  )\ | - --- - | -| (  ( \  ))
(\/  || ))/ ( | -- - -- |  | )) )  \(( 
 ( ()||((( ())|         |  |( (( () )(())''']
library ='''ant baboon badger bat bear beaver camel cat clam cobra cougar
       coyote crow deer dog donkey duck eagle ferret fox frog goat goose hawk
       lion lizard llama mole monkey moose mouse mule newt otter owl panda
       parrot pigeon python rabbit ram rat raven rhino salmon seal shark sheep
       skunk sloth snake spider stork swan tiger toad trout turkey turtle
       weasel whale wolf wombat zebra'''.split()
def SelWord():
    x=random.randint(0,len(library)-1)
    return library[x]
def initial(chooseword):
    print('You have to guess the secret word in 7 times，or it will be game over when the ghost totally appear.')
    print('Take a guess')
    print(picture[0])      #test
    for i in range(len(chooseword)):
        print('_',end=' ')
    print()
    print()
def Guess(correctword,wrongword):
    print('Guess a letter.')
    while True:
            guessword=input()
            guessword=guessword.lower()
            if (len(guessword)!=1):
                print('please input a single letter.')
            elif((guessword in correctword) or (guessword in wrongword)):
                print('The letter has been choosen.Please choose another one')
            elif(guessword not in 'abcdefghijklmnopqrstuvwxyz'):
                print('Please input a letter.')
            else:
                return guessword
def board(selword,correctword,wrongword):
    print(picture[len(wrongword)])
    print()
    #wrongword
    print('Wrong letter:',end=' ')
    for i in wrongword:
        print(i,end=' ')
    print()
    #
    blanks='_'*len(selword)
    for j in range(len(selword)):
        if selword[j] in correctword:
            blanks=blanks[:j]+selword[j]+blanks[j+1:]
    for i in blanks:
        print(i,end=' ')
    print()
def Playagain():
    print('Do you want to play again?Please input (yes,y),or (no,n)')
    again=input()
    again=again.lower()
    while(again!='yes'and again!='y'and again!='no' and again!='n'):
        print('Please input (yes,y),or (no,n)')
        again=input()
        again=again.lower()
    if(again=='yes'or again=='y'):
        return 1
    else:
        return 0
    
correctword=''
wrongword=''
selword=SelWord()
initial(selword)
gameisdone=False
while True:
    guess=Guess(correctword,wrongword)
    if guess in selword:
        correctword=correctword+guess
        board(selword,correctword,wrongword)
        foundAllLetters = True
        for i in range(len(selword)):
             if selword[i] not in correctword:
                 foundAllLetters = False
        if foundAllLetters:
             print('Yes! The secret word is "' + selword +'"! You have won!')
             gameisdone=True
    else:
        wrongword=wrongword+guess
        board(selword,correctword,wrongword)
        if len(wrongword)==len(picture)-1:
             board(selword,correctword,wrongword)
             print('You have run out of guesses!\nAfter ' +str(len(wrongword)) + ' missed guesses and '+str(len(correctword))+' correct guesses,the word was "'+selword+'"')
             gameisdone = True
    if gameisdone:
        playagain=Playagain()
        if(playagain==1):
            correctword=''
            wrongword=''
            selword=SelWord()
            initial(selword)
            gameisdone=False
        else:
            break