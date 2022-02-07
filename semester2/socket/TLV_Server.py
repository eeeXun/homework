import sys,struct,socket

def nbyte_to_data(sock):
    size_info={'B':1,'H':2,'L':4,'Q':8,'d':8}
    
    tag=sock.recv(1).decode('utf-8')
    if not tag:
        return False
    else:
        if tag in size_info:
            size=size_info[tag]
            data=sock.recv(size)
            message=struct.unpack('!'+tag,data)[0]
        elif tag in 'sc':
            length=nbyte_to_data(sock)
            data=sock.recv(length)
            message=data.decode('utf-8')
            
        return message
def server(ip,port):
    listensock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    listensock.bind((ip,port))
    listensock.listen(5)
    
    sock,sockname=listensock.accept()
    while True:
        message=nbyte_to_data(sock)
        if not message:
            break
        else:
            print('receive %s from %s'%(message,sockname))
        
    sock.close()
    listensock.close()
    
if len(sys.argv)!=3:
    print('Wrong format')
else:
    ip=sys.argv[1]
    port=int(sys.argv[2])
    server(ip,port)