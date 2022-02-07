import sys,struct,socket

class NetAPI:
    FILE_TAG_SIZE       = 8
    FILE_END_TAG        = b'FILEEND0'
    FILE_NAME_TAG       = b'FILENAME'
    FILE_SIZE_TAG       = b'FILESIZE'
    FILE_CONTENT_TAG    = b'FILEDATA'
    FILE_ABORT_TAG      = b'FILEABRT'
    
    def __init__(self,s):
        from NetworkIO import NetworkIO
        self.Handle=NetworkIO(s)
        self.savePath   = 'X:\\SaveFiles'
        self.maxSize    = 2147483647
        self.blockSize  = 4096
    
    def send_tag(self,t):
        self.Handle.write_raw(t)
    def send_data(self,d):
        self.Handle.write(d)
    def send_filename(self,n):
        self.send_data(n)
    def send_filesize(self,s):
        self.send_data(s)
    def send_filecontent(self,d):
        self.send_data(d)
        
    def send_file(self,f):
        import os
        filename=self.savePath+'/'+f
        filesize = os.path.getsize(f)
        filedata = open(f, 'rb').read()
        try:
            self.send_tag(self.FILE_NAME_TAG)
            self.send_filename(filename)
            self.send_tag(self.FILE_SIZE_TAG)
            self.send_filesize(filesize)
            self.send_tag(self.FILE_CONTENT_TAG)
            self.send_filecontent(filedata)
            self.send_tag(self.FILE_END_TAG)
            return True
        except Exception as e:
            print(str(e))
            self.send_tag(self.FILE_ABORT_TAG)
            return False
        
    def recv_tag(self):
        return self.Handle.read_raw(self.FILE_TAG_SIZE)
    def recv_data(self):
        return self.Handle.read()
    def split_path(self,path):
        import os
        result=[]
        while True:
            head,tail=os.path.split(path)
            if tail:
                if tail == '..':
                    raise ValueError('Dangerous')
                else:
                    result.insert(0,tail)
                    path=head
            else:
                head=head.strip('/:\\')
                if head:
                    result.insert(0,head)
                break
        return result
    def normalize_path(self,data):
        result=self.split_path(data)
        path='/'.join(result)
        return path
    def recv_file(self):
        result={}
        while True:
            tag=self.recv_tag()
            if not tag or tag in [self.FILE_END_TAG, self.FILE_ABORT_TAG]:
                break
            data=self.recv_data()
            if tag==self.FILE_NAME_TAG:
                data=self.normalize_path(data)
            result[tag]=data
            
        return result
            
def client(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect( (ip, port) )

    handle = NetAPI(sock)
    handle.send_file('a.txt')
    sock.close()
    
def server(ip, port):
    listeningSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    listeningSock.bind( (ip, port) )
    listeningSock.listen()
    print("Listening at", listeningSock.getsockname())

    while True:
        sock, sockname = listeningSock.accept()
        handle = NetAPI(sock)
        while True:
            data = handle.recv_file()
            if not data:
                break
            print('receive  from {}\n{}'.format(sockname, data))
        sock.close()

def main():
    if len(sys.argv)!=4:
        print('Wrong format')
    else:
        ip=sys.argv[2]
        port=int(sys.argv[3])
        if sys.argv[1] == 'client':
            client(ip,port)
        elif sys.argv[1] == 'server':
            server(ip,port)
        else:
            print('Wrong format')
  
if __name__ == "__main__":
    main()