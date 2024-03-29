import socket, sys,threading

MAX_BYTES = 1024
        
def send(sock):
    while True:
        msg = input()
        sock.send( msg.encode('UTF-8') )
    
def read(sock):
    while True:
        data = sock.recv(MAX_BYTES)
        print( data.decode('UTF-8') )
    
def server(host, port):
    listeningSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    listeningSock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    listeningSock.bind( (host, port) )
    listeningSock.listen()
    print("Listening at", listeningSock.getsockname())

    sock, peername = listeningSock.accept()
    s=threading.Thread(target=send,args=(sock,))
    r=threading.Thread(target=read,args=(sock,))
    r.start()
    s.start()

def client(host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect( (host, port) )
    print("Connecting from", sock.getsockname(), "to", sock.getpeername())
    s=threading.Thread(target=send,args=(sock,))
    r=threading.Thread(target=read,args=(sock,))
    s.start()
    r.start()

def main():
    msg = "Usage: %s {server|client} host port" % sys.argv[0]
    if len(sys.argv) != 4:
        print(msg)
    else:
        host = sys.argv[2]
        port = int(sys.argv[3])
        if sys.argv[1] == "server":
            server(host, port)
        elif sys.argv[1] == "client":
            client(host, port)
        else:
            print(msg)

if __name__ == "__main__":
    main()