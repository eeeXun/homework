import socket,sys

def server(ip,port):
    listensock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    listensock.bind((ip,port))
    listensock.listen(5)
    
    sock,sockname=listensock.accept()
    message=sock.recv(1024).decode()
    print(message,'from:',sockname)
    
    sock.close()
    listensock.close()
    
def client(ip,port):
    sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock.connect((ip,port))
    message=input('input sth.').encode('utf-8')
    sock.send(message)
    
    sock.close()

def main():
    if len(sys.argv) != 4:
        print('wrong format')
    else:
        ip=sys.argv[2]
        port=int(sys.argv[3])
        if sys.argv[1] == 'server':
            server(ip,port)
        elif sys.argv[1] == 'client':
            client(ip,port)
        else:
            print('wrong format')

main()