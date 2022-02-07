import random
picture=[
'''                                
                              
                             
                             
                                
                                
             ___`>  -<'___             
                                      
              ,    .    .             
              | .  |  . |             
              | ___|___ |        (     
  ((          | _______ |        ))  ( 
(  )\   (  )\ | - --- - |    (  ( \  ))
(\/     ))/ ( | -- - -- |    )) )  \(( 
 ( ()  ((( ())|         |   ( (( () )(())''',
'''                                
                 _____               
                /     \              
                |     |              
                |     |                
                |     |                
             ___`>  -<'___             
                                      
              ,    .    .             
              | .  |  . |             
              | ___|___ |        (     
  ((          | _______ |        ))  ( 
(  )\   (  )\ | - --- - |    (  ( \  ))
(\/     ))/ ( | -- - -- |    )) )  \(( 
 ( ()  ((( ())|         |   ( (( () )(())''',
'''                                
                 _____               
                /     \              
                |     |              
                |     |                
                |     |                
             ___`>  -<'___             
                          |            
              ,    .    . |            
              | .  |  . | |            
              | ___|___ | |      (     
  ((          | _______ | |      ))  ( 
(  )\   (  )\ | - --- - | |  (  ( \  ))
(\/     ))/ ( | -- - -- | |  )) )  \(( 
 ( ()  ((( ())|         | | ( (( () )(())''',
'''                                
                 _____               
                /     \              
                |     |              
                |     |                
                |     |                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
'''                                
             ,/  _____  \.             
             ||_/     \_||             
              \_|     |_/              
                |     |                
                |     |                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
'''                                
             ,/  _____  \.             
             ||_/     \_||             
              \_| . . |_/              
                |     |                
                |     |                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
'''                                
             ,/  _____  \.             
             ||_/     \_||             
              \_| . . |_/              
                |  L  |                
                |     |                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
'''                                
             ,/  _____  \.             
             ||_/     \_||             
              \_| . . |_/              
                |  L  |                
                |`==='|                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
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
 ( ()||((( ())|         |  |( (( () )(())'''
]
library={'animal':'''ant baboon badger bat bear beaver camel cat clam cobra cougar
        coyote crow deer dog donkey duck eagle ferret fox frog goat goose hawk
        lion lizard llama mole monkey moose mouse mule newt otter owl panda
        parrot pigeon python rabbit ram rat raven rhino salmon seal shark sheep
        skunk sloth snake spider stork swan tiger toad trout turkey turtle
        weasel whale wolf wombat zebra'''.split(),
        'color':'red orange yellow green blue indigo violet white black brown'.split(),
        'shape':'''square triangle rectangle circle ellipse rhombus trapezoid
        chevron pentagon hexagon septagon octagon'''.split(),
        'fruit':'''apple orange lemon lime pear watermelon grape grapefruit cherry
        banana cantaloupe mango strawberry tomato'''.split()
        }
def Getword():
    kind=random.choice(list(library.keys()))
    word=random.choice(library[kind])
    return kind,word
def Difficulty():
    while True:
        print('Enter difficulty: E - Easy , M - Medium , H - Hard')
        difficulty=input()
        difficulty=difficulty.lower()
        getpicture=[]
        if(difficulty=='e' or difficulty=='easy' or difficulty=='m' or difficulty=='medium' or difficulty=='h' or difficulty=='hard'):
            if(difficulty=='m' or difficulty=='medium'):
                del picture[0]
                del picture[0]
            elif(difficulty=='h' or difficulty=='hard'):
                del picture[0]
                del picture[0]
                del picture[0]
                del picture[0]
            break            
def initial(kind,word):
    print('You have to guess the secret word in',len(picture)-1,'times，or it will be game over when the ghost totally appear.')
    print('The secret word is in the set:',kind)
    print(picture[0])
    print()
    for i in range(len(word)):
        print('_',end=' ')
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
def board(correctword,wrongword,word):
    print(picture[len(wrongword)])
    print('Wrong letter:',end='')
    for i in wrongword:
        print(i,end=' ')
    print()
    
    for i in word:
        if(i in correctword):
            print(i,end=' ')
        else:
            print('_',end=' ')
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
       
Difficulty()
kind,word=Getword()
initial(kind,word)
correctword=''
wrongword=''
gameisdone=False
while True:
    getguess=Guess(correctword,wrongword)
    if(getguess in word):
        correctword=correctword+getguess
        board(correctword,wrongword,word)
        foundAllLetter=True
        for i in word:
            if(i not in correctword):
                foundAllLetter=False
        if foundAllLetter:
            print('Yes! The secret word is "'+word+'"! You have won!')
            gameisdone=True
    else:
        wrongword=wrongword+getguess
        board(correctword,wrongword,word)
        if(len(wrongword)==len(picture)-1):
            print('You have run out of guesses!\nAfter',len(wrongword),'missed guesses and',len(correctword),'correct guesses,the word was "',word,'"')
            gameisdone=True
    if gameisdone:
        playagain=Playagain()
        if(playagain==1):
            picture=[
            '''                                
                              
                             
                             
                                
                                
             ___`>  -<'___             
                                      
              ,    .    .             
              | .  |  . |             
              | ___|___ |        (     
  ((          | _______ |        ))  ( 
(  )\   (  )\ | - --- - |    (  ( \  ))
(\/     ))/ ( | -- - -- |    )) )  \(( 
 ( ()  ((( ())|         |   ( (( () )(())''',
          '''                                
                 _____               
                /     \              
                |     |              
                |     |                
                |     |                
             ___`>  -<'___             
                                      
              ,    .    .             
              | .  |  . |             
              | ___|___ |        (     
  ((          | _______ |        ))  ( 
(  )\   (  )\ | - --- - |    (  ( \  ))
(\/     ))/ ( | -- - -- |    )) )  \(( 
 ( ()  ((( ())|         |   ( (( () )(())''',
          '''                                
                 _____               
                /     \              
                |     |              
                |     |                
                |     |                
             ___`>  -<'___             
                          |            
              ,    .    . |            
              | .  |  . | |            
              | ___|___ | |      (     
  ((          | _______ | |      ))  ( 
(  )\   (  )\ | - --- - | |  (  ( \  ))
(\/     ))/ ( | -- - -- | |  )) )  \(( 
 ( ()  ((( ())|         | | ( (( () )(())''',
          '''                                
                 _____               
                /     \              
                |     |              
                |     |                
                |     |                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
          '''                                
             ,/  _____  \.             
             ||_/     \_||             
              \_|     |_/              
                |     |                
                |     |                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
          '''                                
             ,/  _____  \.             
             ||_/     \_||             
              \_| . . |_/              
                |     |                
                |     |                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
          '''                                
             ,/  _____  \.             
             ||_/     \_||             
              \_| . . |_/              
                |  L  |                
                |     |                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
          '''                                
             ,/  _____  \.             
             ||_/     \_||             
              \_| . . |_/              
                |  L  |                
                |`==='|                
             ___`>  -<'___             
       \    /             \            
        \  /  ,    .    .  |           
         \/  /| .  |  . |  |           
       \  ` / | ___|___ |  |     (     
  ((    `--'  | _______ |  |     ))  ( 
(  )\   (  )\ | - --- - | -| (  ( \  ))
(\/     ))/ ( | -- - -- |  | )) )  \(( 
 ( ()  ((( ())|         |  |( (( () )(())''',
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
 ( ()||((( ())|         |  |( (( () )(())'''
            ]
            Difficulty()
            kind,word=Getword()
            correctword=''
            wrongword=''
            gameisdone=False
            initial(kind,word)
        else:
            break