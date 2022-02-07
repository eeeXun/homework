import sys,socket,struct

def data_to_nbyte(message):
    if isinstance(message,int):
        if message < (1<<8):
            tag='B'
        elif message < (1<<16):
            tag='H'
        elif message < (1<<32):
            tag='L'
        else:
            tag='Q'
        message=struct.pack('!'+tag,message)
        
        return tag.encode('utf-8')+message
    elif isinstance(message,float):
        tag='d'
        message=struct.pack('!d',message)
        
        return tag.encode('utf-8')+message
    elif isinstance(message,bytes):
        tag='s'
        
        return tag.encode('utf-8')+data_to_nbyte(len(message))+message
    elif isinstance(message,str):
        tag='c'
        message=message.encode('utf-8')
        
        return tag.encode('utf-8')+data_to_nbyte(len(message))+message
    
def nbyte_to_data(sock):
    size_info={'B':1,'H':2,'L':4,'Q':8,'d':8}
    
    tag=sock.recv(1).decode('utf-8')
    if not tag:
        return False,False
    elif tag in size_info:
        if tag=='d':
            Type='float'
        else:
            Type='int'
        size=size_info[tag]
        number=sock.recv(size)
        message=struct.unpack('!'+tag,number)[0]
    elif tag in 'sc':
        size=nbyte_to_data(sock)[0]
        if tag=='s':
            Type='bytes'
            message=sock.recv(size)
        else:
            Type='str'
            bstr=sock.recv(size)
            message=bstr.decode('utf-8')
    return message,Type
    
def client(host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect( (host, port) )

    sock.send( data_to_nbyte(b'NCNU') )
    sock.send( data_to_nbyte('Happy Birthday') )
    sock.send( data_to_nbyte(5201314) )
    sock.send( data_to_nbyte(3.1415926535) )

    sock.close()
    
def server(ip,port):
    listensock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    listensock.bind((ip,port))
    listensock.listen(5)
    
    sock,sockname=listensock.accept()
    while True:
        message,Type=nbyte_to_data(sock)
        if not message:
            break
        else:
            print('receive',Type,message,'from',sockname)
        
    sock.close()
    listensock.close()
        
def main():
    if len(sys.argv)!=4:
        print('wrong format')
    else:
        ip=sys.argv[2]
        port=int(sys.argv[3])
        if sys.argv[1]=='server':
            server(ip,port)
        elif sys.argv[1]=='client':
            client(ip,port)
        else:
            print('wrong format')
            
main()