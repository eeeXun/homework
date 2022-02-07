Total='A B C D E F G H I J K L M N O P Q R S T U V W X Y Z'
original=Total.split()
symbols=Total.split()

def getKey():
    print('Enter your key')
    while True:
        repeat=False
        key=input()
        for i in range(0,len(key)-1):
            for j in range(i+1,len(key)):
                if(key[i]==key[j]):
                    repeat=True
        if repeat:
            print('There are repeated letter in your key,please input again.')
        else:
            return key
        
def getMode():
    while True:
        print('Please input encrypt(or \'e\') or decrypt(or \'d\').')
        mode=input().lower()
        if mode in ['encrypt','e','decrypt','d']:
            return mode

def getMessage():
        print('Enter your message.')
        return input()
    
def getSymbols(key):
    for i in key:
        symbols.remove(i)
    symbols.reverse()
    for i in range(len(key)-1,-1,-1):
        symbols.append(key[i])
    symbols.reverse()
    
def getTranslate(mode,message):
    translated=''
    if(mode=='encrypt' or mode=='e'):
        for i in range(len(message)):
            if(message[i] not in original):
                translated+=message[i]
            else:
                for j in range(len(original)):
                    if(original[j]==message[i]):
                        translated+=symbols[j]
                        continue
    elif(mode=='decrypt' or mode=='d'):
        for i in range(len(message)):
            if(message[i] not in original):
                translated+=message[i]
            else:
                for j in range(len(symbols)):
                    if(symbols[j]==message[i]):
                        translated+=original[j]
                        continue
    return translated

key=getKey()
mode=getMode()
message=getMessage()
getSymbols(key)
print('Your translated text is:',end='')
translated=getTranslate(mode,message)
print(translated)