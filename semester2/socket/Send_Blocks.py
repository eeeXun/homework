import sys,struct,socket

class NetAPI:
    FILE_TAG_SIZE       = 8
    FILE_END_TAG        = b'FILEEND0'
    FILE_NAME_TAG       = b'FILENAME'
    FILE_SIZE_TAG       = b'FILESIZE'
    FILE_CONTENT_TAG    = b'FILEDATA'
    FILE_ABORT_TAG      = b'FILEABRT'
    FILE_BLOCKS_TAG     = b'FILEBLKS'
    maxsize             = 4096
    
    def __init__(self,s):
        from NetworkIO import NetworkIO
        self.Handle=NetworkIO(s)
        self.savePath   = 'D:\\Users\Desktop\save_file'
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
    def send_blocks(self,f):
        fp=open(f,'rb')
        blockID=0
        totalSize=0
        while True:
            block=fp.read(self.maxsize)
            if not block:
                break
            blockID+=1
            self.send_data(blockID)
            self.send_data(block)
            totalSize+=len(block)
        self.send_data(0)
        return totalSize
        
    def send_file(self,f):
        import os
        filename=self.savePath+'/'+f
        filesize = os.path.getsize(f)
        self.send_tag(self.FILE_NAME_TAG)
        self.send_filename(filename)
        self.send_tag(self.FILE_SIZE_TAG)
        self.send_filesize(filesize)
        if filesize>self.maxsize:
            self.send_tag(self.FILE_BLOCKS_TAG)
            self.send_blocks(f)
        else:
            filedata = open(f,'rb').read()
            self.send_tag(self.FILE_CONTENT_TAG)
            self.send_filecontent(filedata)
            self.send_tag(self.FILE_END_TAG)
            return True
        
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
    def recv_blocks(self):
        import time,os
        totalSize=0
        lastBlockID=0
        filename=os.path.join(self.savePath,'TEMP%x'%int(time.time()))
        dirname=os.path.dirname(filename)
        if not os.path.exists(dirname):
            os.makedirs(dirname)
        with open(filename,'wb') as fp:
            while True:
                blockID=self.recv_data()
                if not isinstance(blockID,int):
                    raise TypeError('invalid type of block id %s'%type(blockID))
                if blockID==0:
                    break
                if lastBlockID+1 != blockID:
                    raise ValueError('block id error,last:%d,current%d'%(lastBlockID,blockID))
                lastBlockID=blockID
                block=self.recv_data()
                if not isinstance(block,bytes):
                    raise TypeError('invalid type of block %s'%type(block))
                if len(block)+totalSize>self.maxsize:
                    raise RuntimeError('exceed max file size limit')
                fp.write(block)
        return filename
    def recv_file(self):
        result={}
        while True:
            tag=self.recv_tag()
            if not tag or tag in [self.FILE_END_TAG, self.FILE_ABORT_TAG]:
                break
            if tag==self.FILE_BLOCKS_TAG:
                filename=self.recv_blocks()
                result[tag]=filename
            else:
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
    
def save_file(fileInfo,target):
    import os,shutil
    filename=fileInfo.get(NetAPI.FILE_NAME_TAG)
    filesize=fileInfo.get(NetAPI.FILE_SIZE_TAG)
    filecontent=fileInfo.get(NetAPI.FILE_CONTENT_TAG)
    filetemp=fileInfo.get(NetAPI.FILE_BLOCKS_TAG)
    if not filename or not filesize:
        return False
    if filecontent or filetemp:
        fullname=os.path.join(target,filename)
        dirname=os.path.dirname(fullname)
        if not os.path.exists(dirname):
            os.makedirs(dirname)
        if filecontent:
            if len(filecontent) != filesize:
                raise RuntimeError('size unmatched')
            with open(fullname,'wb') as fp:
                fp.write(filecontent)
        else:
            if os.path.getsize(filetemp) != filesize:
                raise RuntimeError('size unmatched')
            shutil.move(filetemp,fullname)
        return True
    else:
        return False
    
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
            print('Do you wanna save file in desktop?\'y\' to save')
            if input()=='y':
                save_file(data,'D:\\Users\\Desktop')
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