import sys,struct,socket

def data_to_nbyte(message):
    if isinstance(message,int):
        if message<(1<<8):
            tag='B'
        elif message<(1<<16):
            tag='H'
        elif message<(1<<32):
            tag='L'
        else:
            tag='Q'
        message=struct.pack('!'+tag,message)
        return tag.encode('utf-8')+message
    elif isinstance(message,float):
        tag='d'
        message=struct.pack('!'+tag,message)
        return tag.encode('utf-8')+message
    elif isinstance(message,bytes):
        tag='s'
        return tag.encode('utf-8')+data_to_nbyte(len(message))+message
    elif isinstance(message,str):
        tag='c'
        message=message.encode('utf-8')
        return tag.encode('utf-8')+data_to_nbyte(len(message))+message
    
def client(ip,port):
    sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock.connect((ip,port))
    Type=input('Which type do you wannna send,int,float,bytes or str?')
    if Type=='int':
        message=int(input('Send a integer :'))
    elif Type=='float':
        message=float(input('Send a float :'))
    elif Type=='bytes':
        message=(input('Send a string :')).encode('utf-8')
    elif Type=='str':
        message==input('Send a string :')
    else:
        print('There is no type %s'%(Type))
        sys.exit()
    sock.send(data_to_nbyte(message))
    
    sock.close()
    
if len(sys.argv)!=3:
    print('Wrong format')
else:
    ip=sys.argv[1]
    port=int(sys.argv[2])
    client(ip,port)